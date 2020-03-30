#pragma once
#include "TMuffinSysInclude.h"

class CMesh;
class SBoneDetail;
class CAnimator;
class T_DLL_EXPORT CAnimation
{
private:
	const aiScene* m_pAIScene;
	hash_map<tstring, SBoneDetail*> m_mapName2Bone;
	glm::mat4 m_matInverseTransformation;
	f32 m_fNowPlayTime;
	tbool m_bIsEnd;
	CAnimator* m_pAnimator;

public:
	tbool m_bIsLoop;
	tstring m_strName;

private:
	void ReadNodeHeirarchy(f32 a_fAnimationTime, const aiNode* a_pNode, const glm::mat4& a_ParentTransform);

	void CalcGLMInterpolatedRotation(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::quat& a_qOut);
	void CalcGLMInterpolatedPosition(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut);
	void CalcGLMInterpolatedScaling(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut);

	void CalcInterpolatedRotation(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiQuaternion& out);
	void CalcInterpolatedPosition(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiVector3D& out);
	void CalcInterpolatedScaling(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, aiVector3D& out);

public:
	CAnimation();
	~CAnimation();

	tbool Init(const tcchar* a_pFileName);
	void GetBoneTransform(vector<glm::mat4>& a_vecTransform);

	f32 GetDuration();
	tbool IsPlaying();
	void Reset();
	void SetAnimator(CAnimator* a_pAnimator);
};
