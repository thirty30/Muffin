#pragma once

struct SMeshColliderTriangle
{
	glm::vec3 m_vPoint1;
	glm::vec3 m_vPoint2;
	glm::vec3 m_vPoint3;
	glm::vec3 m_vTriangleNormal;
};

struct SMeshColliderBox
{
	vector<n32> m_vecTriangleIdx;
	glm::vec3 m_fMinPoint;
	glm::vec3 m_fMaxPoint;
};

class T_DLL_EXPORT CColliderMesh : public CColliderBase
{
#define SUB_STEP_NUM 10
public:
	n32 m_nTriangleCount;
	SMeshColliderTriangle* m_pTriangleoArray;
	
	hash_map<u64, SMeshColliderBox*> m_mapID2AABB;

	glm::vec3 m_vMinPoint;
	glm::vec3 m_vMaxPoint;

	n32 m_nXStepNum;
	n32 m_nYStepNum;
	n32 m_nZStepNum;

	f32 m_fXStep;
	f32 m_fYStep;
	f32 m_fZStep;

private:
	SMeshColliderBox* GetBoxByID(u64 a_nID);

public:
	CColliderMesh();
	~CColliderMesh();

	SMeshColliderBox* FindBoxByPosition(glm::vec3 a_vPosition);
	virtual void SetScale(glm::vec3 a_vScale) {}
	void InitColliderMesh(CMesh* a_pMesh);
};
