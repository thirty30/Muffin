#include "CAnimation.h"
#include "Utility/Utility.h"
#include "Graphics/Mesh/CMesh.h"

CAnimation::CAnimation()
{
	this->m_pAIScene = NULL;
	this->m_fNowTime = 0;
}

CAnimation::~CAnimation()
{

}

tbool CAnimation::Init(const tcchar* a_pFileName, CMesh* a_pMesh)
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

	if (a_pMesh == NULL)
	{
		return false;
	}

	this->m_matInverseTransformation = a_pMesh->m_matInverseTransformation;
	for (auto iter : a_pMesh->m_mapName2Bone)
	{
		SBoneDetail* pOri = iter.second;
		SBoneDetail* pNow = new SBoneDetail(*pOri);
		this->m_mapName2Bone[iter.first] = pNow;
	}
	return true;
}

void CAnimation::GetBoneTransform(f32 a_fTimeInSeconds, vector<glm::mat4>& a_vecTransform)
{
	glm::mat4 matIdentity(1.0f);
	f32 TicksPerSecond = this->m_pAIScene->mAnimations[0]->mTicksPerSecond != 0 ? this->m_pAIScene->mAnimations[0]->mTicksPerSecond : 25.0f;

	f32 TimeInTicks = a_fTimeInSeconds * TicksPerSecond;
	f32 AnimationTime = fmod(TimeInTicks, this->m_pAIScene->mAnimations[0]->mDuration);

	this->ReadNodeHeirarchy(AnimationTime, this->m_pAIScene->mRootNode, matIdentity);

	n32 nNumBones = this->m_mapName2Bone.size();
	a_vecTransform.resize(nNumBones);

	for (auto iter : this->m_mapName2Bone)
	{
		SBoneDetail* pDetail = iter.second;
		a_vecTransform[pDetail->boneID] = pDetail->FinalTransformation;
	}
}

void CAnimation::ReadNodeHeirarchy(f32 a_fAnimationTime, const aiNode* a_pNode, const glm::mat4& a_ParentTransform)
{
	tstring strNodeName(a_pNode->mName.C_Str());

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
		glm::vec3 vScale;
		this->CalcGLMInterpolatedScaling(a_fAnimationTime, pNodeAnimation, vScale);
		glm::mat4 matScale = glm::scale(glm::mat4(1.0f), vScale);

		// Get interpolated rotation (quaternion)
		glm::quat qRotation;
		this->CalcGLMInterpolatedRotation(a_fAnimationTime, pNodeAnimation, qRotation);
		glm::mat4 matRotation = glm::mat4_cast(qRotation);

		// Get interpolated position 
		glm::vec3 vPosition;
		this->CalcGLMInterpolatedPosition(a_fAnimationTime, pNodeAnimation, vPosition);
		glm::mat4 matPosition = glm::translate(glm::mat4(1.0f), vPosition);

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
