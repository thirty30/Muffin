#pragma once

//////////////////////////////////////////////////////////////
//CBaseCollider
class CBaseCollider : public CComponent
{
public:
	EColliderType m_eColliderType;
	glm::vec3 m_vCenter;

	CBaseCollider() 
	{
		this->m_eColliderType = E_COLLIDER_TYPE_INIT;
		this->m_vCenter = glm::vec3(0, 0, 0);
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
		this->m_vSize = glm::vec3(1, 1, 1);
	}
	~CBoxCollider() {}

	virtual void SetScale(glm::vec3 a_vScale)
	{
		this->m_vSize = a_vScale;
	}
};

//////////////////////////////////////////////////////////////
//CMeshCollider
class CMeshCollider : public CBaseCollider
{
public:
	CMesh m_objMesh;
	CMeshCollider()
	{
		this->m_eComponentType = E_COMPONENT_MESH_COLLIDER;
		this->m_eColliderType = E_COLLIDER_TYPE_MESH;
	}
	~CMeshCollider() {}

	virtual void SetScale(glm::vec3 a_vScale) {}
};

