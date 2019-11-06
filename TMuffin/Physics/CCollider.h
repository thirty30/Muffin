#pragma once

//////////////////////////////////////////////////////////////
//CBaseCollider
class T_DLL_EXPORT CBaseCollider
{
public:
	EColliderType m_eColliderType;
	glm::vec3 m_vCenter;
	f32 m_fElastic;
	tbool m_bIsTrigger;

	CBaseCollider();
	virtual ~CBaseCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) T_PURE;
};

//////////////////////////////////////////////////////////////
//CPlaneCollider
class T_DLL_EXPORT CPlaneCollider : public CBaseCollider
{
public:
	EPLaneColliderAxis m_eAxis;
	f32 m_fPos;

	CPlaneCollider();
	~CPlaneCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) {}
};

//////////////////////////////////////////////////////////////
//CSphereCollider
class T_DLL_EXPORT CSphereCollider : public CBaseCollider
{
public:
	f32 m_fRadius;
	CSphereCollider();
	~CSphereCollider() {}

	virtual void SetScale(glm::vec3 a_vScale);
};

//////////////////////////////////////////////////////////////
//CBoxCollider
class T_DLL_EXPORT CBoxCollider : public CBaseCollider
{
public:
	glm::vec3 m_vSize;
	CBoxCollider();
	~CBoxCollider() {}

	virtual void SetScale(glm::vec3 a_vScale)
	{
		this->m_vSize = a_vScale;
	}

	T_INLINE glm::vec3 GetMinPoint()
	{
		return glm::vec3(this->m_vCenter.x - this->m_vSize.x, this->m_vCenter.y - this->m_vSize.y, this->m_vCenter.z - this->m_vSize.z);
	}

	T_INLINE glm::vec3 GetMaxPoint()
	{
		return glm::vec3(this->m_vCenter.x + this->m_vSize.x, this->m_vCenter.y + this->m_vSize.y, this->m_vCenter.z + this->m_vSize.z);
	}
};

//////////////////////////////////////////////////////////////
//CMeshCollider
struct sMeshColliderTriangle
{
	glm::vec3 m_vPoint1;
	glm::vec3 m_vPoint2;
	glm::vec3 m_vPoint3;
	glm::vec3 m_vTriangleNormal;

	u32 m_nDebugIdx1;
	u32 m_nDebugIdx2;
	u32 m_nDebugIdx3;
};

struct T_DLL_EXPORT sMeshColliderBox
{
	vector<n32> m_vecTriangleIdx;
	glm::vec3 m_fMinPoint;
	glm::vec3 m_fMaxPoint;
};

class T_DLL_EXPORT CMeshCollider : public CBaseCollider
{
#define SUB_STEP_NUM 10
public:
	sMeshColliderTriangle* m_pTriangleoArray;
	n32 m_nTriangleCount;
	hash_map<u64, sMeshColliderBox*> m_mapID2AABB;

	glm::vec3 m_vMinPoint;
	glm::vec3 m_vMaxPoint;

	n32 m_nXStepNum;
	n32 m_nYStepNum;
	n32 m_nZStepNum;

	f32 m_fXStep;
	f32 m_fYStep;
	f32 m_fZStep;

private:
	sMeshColliderBox* GetBoxByID(u64 a_nID);
	
	
public:
	CMeshCollider();
	~CMeshCollider();

	sMeshColliderBox* FindBoxByPosition(glm::vec3 a_vPosition);
	virtual void SetScale(glm::vec3 a_vScale) {}
	void InitColliderMesh(CMesh* a_pMesh);
};

