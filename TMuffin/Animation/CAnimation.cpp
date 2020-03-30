#include "CAnimation.h"
#include "Utility/Utility.h"
#include "AssetsLoader/AssetObject/CMesh.h"
#include "Graphics/CGraphicsComponent.h"
#include "GameObject/CGameObject.h"
#include "CAnimator.h"


CAnimation::CAnimation()
{
	this->m_pAIScene = NULL;
	this->m_fNowPlayTime = 0;
	this->m_bIsLoop = true;
	this->m_bIsEnd = false;
	this->m_pAnimator = NULL;
}

CAnimation::~CAnimation()
{

}

tbool CAnimation::Init(const tcchar* a_pFileName)
{
	Assimp::Importer* pImporter = new Assimp::Importer();
	this->m_pAIScene = pImporter->ReadFile(a_pFileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GlobalScale |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph);
	if (this->m_pAIScene == NULL || this->m_pAIScene->HasAnimations() == false)
	{
		return false;
	}

	CGraphicsComponent* pGraphics = this->m_pAnimator->GetGameObject()->GetComponent<CGraphicsComponent>();
	CMesh* pMesh = pGraphics->GetMesh();
	if (pMesh == NULL)
	{
		return false;
	}
	this->m_matInverseTransformation = pMesh->m_matInverseTransformation;
	for (auto iter : pMesh->m_mapName2Bone)
	{
		SBoneDetail* pOri = iter.second;
		SBoneDetail* pNow = new SBoneDetail(*pOri);
		this->m_mapName2Bone[iter.first] = pNow;
	}
	return true;
}

void CAnimation::GetBoneTransform(vector<glm::mat4>& a_vecTransform)
{
	if (this->m_bIsEnd == true)
	{
		a_vecTransform.resize(1);
		a_vecTransform.push_back(glm::mat4(1.0f));
		return;
	}
	if (this->m_fNowPlayTime >= this->GetDuration())
	{
		this->m_fNowPlayTime = 0;
		if (this->m_bIsLoop == false)
		{
			this->m_bIsEnd = true;
			a_vecTransform.resize(1);
			a_vecTransform.push_back(glm::mat4(1.0f));
			if (this->m_pAnimator != NULL)
			{
				this->m_pAnimator->CallBackEndAnimation();
			}
			return;
		}
	}

	glm::mat4 matIdentity(1.0f);
	f32 TicksPerSecond = this->m_pAIScene->mAnimations[0]->mTicksPerSecond != 0 ? this->m_pAIScene->mAnimations[0]->mTicksPerSecond : 25.0f;

	f32 TimeInTicks = this->m_fNowPlayTime * TicksPerSecond;
	f32 AnimationTime = fmod(TimeInTicks, this->m_pAIScene->mAnimations[0]->mDuration);

	this->ReadNodeHeirarchy(AnimationTime, this->m_pAIScene->mRootNode, matIdentity);

	n32 nNumBones = this->m_mapName2Bone.size();
	a_vecTransform.resize(nNumBones);

	for (auto iter : this->m_mapName2Bone)
	{
		SBoneDetail* pDetail = iter.second;
		a_vecTransform[pDetail->boneID] = pDetail->FinalTransformation;
	}

	this->m_fNowPlayTime += 0.01f;
}

void CAnimation::ReadNodeHeirarchy(f32 a_fAnimationTime, const aiNode* a_pNode, const glm::mat4& a_ParentTransform)
{
	tstring strNodeName(a_pNode->mName.data);

	const aiAnimation* pAnimation = this->m_pAIScene->mAnimations[0];
	glm::mat4 NodeTransformation = AIMatrixToGLMMatrix(a_pNode->mTransformation);
	const aiNodeAnim* pNodeAnimation = NULL;

	for (n32 i = 0; i < pAnimation->mNumChannels; i++)
	{
		if (pAnimation->mChannels[i]->mNodeName == a_pNode->mName)
		{
			pNodeAnimation = pAnimation->mChannels[i];
			break;
		}
	}

	if (pNodeAnimation != NULL)
	{
		// Interpolate scaling and generate scaling transformation matrix
		//glm::vec3 vScale;
		//this->CalcGLMInterpolatedScaling(a_fAnimationTime, pNodeAnimation, vScale);
		//glm::mat4 matScale = glm::scale(glm::mat4(1.0f), vScale);
		//
		//// Get interpolated rotation (quaternion)
		//glm::quat qRotation;
		//this->CalcGLMInterpolatedRotation(a_fAnimationTime, pNodeAnimation, qRotation);
		//glm::mat4 matRotation = glm::mat4_cast(qRotation);
		//
		//// Get interpolated position 
		//glm::vec3 vPosition;
		//this->CalcGLMInterpolatedPosition(a_fAnimationTime, pNodeAnimation, vPosition);
		//glm::mat4 matPosition = glm::translate(glm::mat4(1.0f), vPosition);
		//
		//// Combine the above transformations
		//NodeTransformation = matPosition * matRotation * matScale;		

		//////////////////////////////////////////////////////////////////////////////

		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D Scaling;
		this->CalcInterpolatedScaling(a_fAnimationTime, pNodeAnimation, Scaling);
		glm::mat4 matScale = glm::scale(glm::mat4(1.0f), glm::vec3(Scaling.x, Scaling.y, Scaling.z));

		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(a_fAnimationTime, pNodeAnimation, RotationQ);
		glm::mat4 matRotation = glm::mat4_cast(glm::quat(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z));

		// Interpolate translation and generate translation transformation matrix
		aiVector3D Translation;
		CalcInterpolatedPosition(a_fAnimationTime, pNodeAnimation, Translation);
		glm::mat4 matPosition = glm::translate(glm::mat4(1.0f), glm::vec3(Translation.x, Translation.y, Translation.z));

		// Combine the above transformations
		NodeTransformation = matPosition * matRotation * matScale;
	}
	
	glm::mat4 ObjectTransformation = a_ParentTransform * NodeTransformation;
	

	hash_map<tstring, SBoneDetail*>::const_iterator iter = this->m_mapName2Bone.find(strNodeName);
	if (iter != this->m_mapName2Bone.end())
	{
		SBoneDetail* pDetail = iter->second;
		pDetail->ObjectBoneTransformation = ObjectTransformation;
		pDetail->FinalTransformation = this->m_matInverseTransformation * ObjectTransformation * pDetail->BoneOffset;
	}

	for (n32 i = 0; i < a_pNode->mNumChildren; i++) {
		this->ReadNodeHeirarchy(a_fAnimationTime, a_pNode->mChildren[i], ObjectTransformation);
	}
}

void CAnimation::CalcGLMInterpolatedRotation(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::quat& a_qOut)
{
	if (a_pNodeAnim->mNumRotationKeys == 1)
	{
		a_qOut.w = a_pNodeAnim->mRotationKeys[0].mValue.w;
		a_qOut.x = a_pNodeAnim->mRotationKeys[0].mValue.x;
		a_qOut.y = a_pNodeAnim->mRotationKeys[0].mValue.y;
		a_qOut.z = a_pNodeAnim->mRotationKeys[0].mValue.z;
		return;
	}
	n32 RotationIndex = 0;
	for (n32 i = 0; i < a_pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mRotationKeys[i + 1].mTime)
		{
			RotationIndex = i;
			break;
		}
	}
	n32 NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < a_pNodeAnim->mNumRotationKeys);
	f32 DeltaTime = (f32)(a_pNodeAnim->mRotationKeys[NextRotationIndex].mTime - a_pNodeAnim->mRotationKeys[RotationIndex].mTime);
	f32 Factor = (a_fAnimationTime - (float)a_pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	if (Factor < 0.0f) Factor = 0.0f;
	if (Factor > 1.0f) Factor = 1.0f;
	const aiQuaternion& StartRotationQ = a_pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = a_pNodeAnim->mRotationKeys[NextRotationIndex].mValue;

	glm::quat StartGLM = glm::quat(StartRotationQ.w, StartRotationQ.x, StartRotationQ.y, StartRotationQ.z);
	glm::quat EndGLM = glm::quat(EndRotationQ.w, EndRotationQ.x, EndRotationQ.y, EndRotationQ.z);

	a_qOut = glm::slerp(StartGLM, EndGLM, Factor);
	a_qOut = glm::normalize(a_qOut);
}

void CAnimation::CalcGLMInterpolatedPosition(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut)
{
	if (a_pNodeAnim->mNumPositionKeys == 1)
	{
		a_vOut.x = a_pNodeAnim->mPositionKeys[0].mValue.x;
		a_vOut.y = a_pNodeAnim->mPositionKeys[0].mValue.y;
		a_vOut.z = a_pNodeAnim->mPositionKeys[0].mValue.z;
		return;
	}

	n32 PositionIndex = 0;
	for (n32 i = 0; i != a_pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mPositionKeys[i + 1].mTime)
		{
			PositionIndex = i;
			break;
		}
	}
	n32 NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < a_pNodeAnim->mNumPositionKeys);
	f32 DeltaTime = (f32)(a_pNodeAnim->mPositionKeys[NextPositionIndex].mTime - a_pNodeAnim->mPositionKeys[PositionIndex].mTime);
	f32 Factor = (a_fAnimationTime - (f32)a_pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	if (Factor < 0.0f) Factor = 0.0f;
	if (Factor > 1.0f) Factor = 1.0f;
	const aiVector3D& StartPosition = a_pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& EndPosition = a_pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	glm::vec3 start = glm::vec3(StartPosition.x, StartPosition.y, StartPosition.z);
	glm::vec3 end = glm::vec3(EndPosition.x, EndPosition.y, EndPosition.z);
	a_vOut = (end - start) * Factor + start;
}

void CAnimation::CalcGLMInterpolatedScaling(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut)
{
	if (a_pNodeAnim->mNumScalingKeys == 1)
	{
		a_vOut.x = a_pNodeAnim->mScalingKeys[0].mValue.x;
		a_vOut.y = a_pNodeAnim->mScalingKeys[0].mValue.y;
		a_vOut.z = a_pNodeAnim->mScalingKeys[0].mValue.z;
		return;
	}

	n32 ScalingIndex = 0;
	for (n32 i = 0; i != a_pNodeAnim->mNumScalingKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mScalingKeys[i + 1].mTime)
		{
			ScalingIndex = i;
			break;
		}
	}
	n32 NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < a_pNodeAnim->mNumScalingKeys);
	f32 DeltaTime = (f32)(a_pNodeAnim->mScalingKeys[NextScalingIndex].mTime - a_pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	f32 Factor = (a_fAnimationTime - (float)a_pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	if (Factor < 0.0f) Factor = 0.0f;
	if (Factor > 1.0f) Factor = 1.0f;
	const aiVector3D& StartScale = a_pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& EndScale = a_pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	glm::vec3 start = glm::vec3(StartScale.x, StartScale.y, StartScale.z);
	glm::vec3 end = glm::vec3(EndScale.x, EndScale.y, EndScale.z);
	a_vOut = (end - start) * Factor + start;
}

void CAnimation::CalcInterpolatedRotation(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiQuaternion& out)
{
	if (a_pNodeAnim->mNumRotationKeys == 1)
	{
		out = a_pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	n32 RotationIndex = 0;
	for (n32 i = 0; i < a_pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mRotationKeys[i + 1].mTime)
		{
			RotationIndex = i;
			break;
		}
	}
	n32 NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < a_pNodeAnim->mNumRotationKeys);
	float DeltaTime = (f32)(a_pNodeAnim->mRotationKeys[NextRotationIndex].mTime - a_pNodeAnim->mRotationKeys[RotationIndex].mTime);
	f32 Factor = (a_fAnimationTime - (f32)a_pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = a_pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = a_pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(out, StartRotationQ, EndRotationQ, Factor);
	out = out.Normalize();
}

void CAnimation::CalcInterpolatedPosition(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiVector3D& out)
{
	if (a_pNodeAnim->mNumPositionKeys == 1)
	{
		out = a_pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	n32 PositionIndex = 0;
	for (n32 i = 0; i != a_pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mPositionKeys[i + 1].mTime)
		{
			PositionIndex = i;
			break;
		}
	}
	n32 NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < a_pNodeAnim->mNumPositionKeys);
	f32 DeltaTime = (f32)(a_pNodeAnim->mPositionKeys[NextPositionIndex].mTime - a_pNodeAnim->mPositionKeys[PositionIndex].mTime);
	f32 Factor = (a_fAnimationTime - (float)a_pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& StartPosition = a_pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& EndPosition = a_pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	out = (EndPosition - StartPosition) * Factor + StartPosition;
}

void CAnimation::CalcInterpolatedScaling(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiVector3D& out)
{
	if (a_pNodeAnim->mNumScalingKeys == 1)
	{
		out = a_pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	n32 ScalingIndex = 0;
	for (n32 i = 0; i != a_pNodeAnim->mNumScalingKeys - 1; i++)
	{
		if (a_fAnimationTime < (f32)a_pNodeAnim->mScalingKeys[i + 1].mTime)
		{
			ScalingIndex = i;
			break;
		}
	}
	n32 NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < a_pNodeAnim->mNumScalingKeys);
	f32 DeltaTime = (f32)(a_pNodeAnim->mScalingKeys[NextScalingIndex].mTime - a_pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	f32 Factor = (a_fAnimationTime - (f32)a_pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& StartScale = a_pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& EndScale = a_pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	out = (EndScale - StartScale) * Factor + StartScale;
}

f32 CAnimation::GetDuration()
{
	return (f32)(this->m_pAIScene->mAnimations[0]->mDuration / this->m_pAIScene->mAnimations[0]->mTicksPerSecond);
}

tbool CAnimation::IsPlaying()
{
	if (this->m_bIsEnd == false && this->m_fNowPlayTime > 0)
	{
		return true;
	}
	return false;
}

void CAnimation::Reset()
{
	this->m_bIsEnd = false;
	this->m_fNowPlayTime = 0;
}

void CAnimation::SetAnimator(CAnimator* a_pAnimator)
{
	this->m_pAnimator = a_pAnimator;
}

