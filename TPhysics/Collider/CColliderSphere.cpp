#include "CColliderSphere.h"

CColliderSphere::CColliderSphere() : CColliderBase(E_SPHERE_COLLIDER)
{
	this->m_fRadius = 1.0f;
}

CColliderSphere::~CColliderSphere()
{

}

void CColliderSphere::SetScale(glm::vec3 a_vScale)
{
	f32 fScale = 0;
	fScale = glm::max(a_vScale.x, a_vScale.y);
	fScale = glm::max(fScale, a_vScale.z);
	this->m_fRadius *= fScale;
}

