#pragma once
#include "TMuffinSysInclude.h"

class CMesh;
class SBoneDetail;
class T_DLL_EXPORT CAnimation
{
private:
	const aiScene* m_pAIScene;
	hash_map<tstring, SBoneDetail*> m_mapName2Bone;
	glm::mat4 m_matInverseTransformation;

public:
	f32 m_fNowTime;

public:
	CAnimation();
	~CAnimation();

	tbool Init(const tcchar* a_pFileName, CMesh* a_pMesh);
	void GetBoneTransform(f32 a_fTimeInSeconds, vector<glm::mat4>& a_vecTransform);
	void ReadNodeHeirarchy(f32 a_fAnimationTime, const aiNode* a_pNode, const glm::mat4& a_ParentTransform);

	void CalcGLMInterpolatedRotation(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::quat& a_qOut);
	void CalcGLMInterpolatedPosition(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut);
	void CalcGLMInterpolatedScaling(f32 a_fAnimationTime, const aiNodeAnim* a_pNodeAnim, glm::vec3& a_vOut);
};
