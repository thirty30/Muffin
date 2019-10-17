#pragma once

//////////////////////////////////////////////////////////////
//CBaseCollider
class CBaseCollider : public CComponent
{
public:
	EColliderType m_eColliderType;
	glm::vec3 m_vCenter;
	f32 m_fElastic;
	tbool m_bIsTrigger;

	CBaseCollider() 
	{
		this->m_eColliderType = E_COLLIDER_TYPE_INIT;
		this->m_vCenter = glm::vec3(0, 0, 0);
		this->m_fElastic = 1.0f;
		this->m_bIsTrigger = false;
	}
	virtual ~CBaseCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) T_PURE;
};

//////////////////////////////////////////////////////////////
//CPlaneCollider
class CPlaneCollider : public CBaseCollider
{
public:
	EPLaneColliderAxis m_eAxis;
	f32 m_fPos;

	CPlaneCollider()
	{
		this->m_eComponentType = E_COMPONENT_PLANE_COLLIDER;
		this->m_eColliderType = E_COLLIDER_TYPE_PLANE;
		this->m_eAxis = E_PLANE_COLLIDER_AXIS_INIT;
		this->m_fPos = 0;
	}
	~CPlaneCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) {}
};

//////////////////////////////////////////////////////////////
//CSphereCollider
class CSphereCollider : public CBaseCollider
{
public:
	f32 m_fRadius;
	CSphereCollider()
	{
		this->m_eComponentType = E_COMPONENT_SPHERE_COLLIDER;
		this->m_eColliderType = E_COLLIDER_TYPE_SPHERE;
		this->m_fRadius = 1.0f;
	}
	~CSphereCollider() {}

	virtual void SetScale(glm::vec3 a_vScale)
	{
		f32 fScale = 0;
		fScale = glm::max(a_vScale.x, a_vScale.y);
		fScale = glm::max(fScale, a_vScale.z);
		this->m_fRadius *= fScale;
	}
};

//////////////////////////////////////////////////////////////
//CBoxCollider
class CBoxCollider : public CBaseCollider
{
public:
	glm::vec3 m_vSize;
	CBoxCollider()
	{
		this->m_eComponentType = E_COMPONENT_BOX_COLLIDER;
		this->m_eColliderType = E_COLLIDER_TYPE_BOX;
		this->m_vSize = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	~CBoxCollider() {}

	virtual void SetScale(glm::vec3 a_vScale)
	{
		this->m_vSize = a_vScale;
	}

	glm::vec3 GetMinPoint()
	{
		return glm::vec3(this->m_vCenter.x - this->m_vSize.x, this->m_vCenter.y - this->m_vSize.y, this->m_vCenter.z - this->m_vSize.z);
	}

	glm::vec3 GetMaxPoint()
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
};

class CMeshCollider : public CBaseCollider
{
public:
	sMeshColliderTriangle* m_pTriangleoArray;
	n32 m_nTriangleCount;

public:
	CMeshCollider()
	{
		this->m_eComponentType = E_COMPONENT_MESH_COLLIDER;
		this->m_eColliderType = E_COLLIDER_TYPE_MESH;
		this->m_pTriangleoArray = NULL;
	}
	~CMeshCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) {}
	void InitColliderMesh(CMesh* a_pMesh)
	{
		this->m_nTriangleCount = a_pMesh->m_nTriangleCount;
		this->m_pTriangleoArray = new sMeshColliderTriangle[this->m_nTriangleCount];
		for (n32 i = 0; i < this->m_nTriangleCount; i++)
		{
			SMeshTriangle* pTriangle = &a_pMesh->m_pTriangles[i];
			sMeshColliderTriangle* pInfo = &this->m_pTriangleoArray[i];
			pInfo->m_vPoint1.x = a_pMesh->m_pVertices[pTriangle->Vertex1].x;
			pInfo->m_vPoint1.y = a_pMesh->m_pVertices[pTriangle->Vertex1].y;
			pInfo->m_vPoint1.z = a_pMesh->m_pVertices[pTriangle->Vertex1].z;

			pInfo->m_vPoint2.x = a_pMesh->m_pVertices[pTriangle->Vertex2].x;
			pInfo->m_vPoint2.y = a_pMesh->m_pVertices[pTriangle->Vertex2].y;
			pInfo->m_vPoint2.z = a_pMesh->m_pVertices[pTriangle->Vertex2].z;

			pInfo->m_vPoint3.x = a_pMesh->m_pVertices[pTriangle->Vertex3].x;
			pInfo->m_vPoint3.y = a_pMesh->m_pVertices[pTriangle->Vertex3].y;
			pInfo->m_vPoint3.z = a_pMesh->m_pVertices[pTriangle->Vertex3].z;

			glm::vec3 vNormal1 = glm::normalize(pInfo->m_vPoint2 - pInfo->m_vPoint1);
			glm::vec3 vNormal2 = glm::normalize(pInfo->m_vPoint3 - pInfo->m_vPoint1);
			pInfo->m_vTriangleNormal = glm::normalize(glm::cross(vNormal1, vNormal2));
		}
	}
};

