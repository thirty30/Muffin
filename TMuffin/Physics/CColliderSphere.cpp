#include "pch.h"

CColliderSphere::CColliderSphere() : CColliderBase(E_COLLIDER_TYPE_SPHERE)
{
	this->m_fRadius = 1.0f;
}

CColliderSphere::~CColliderSphere()
{

}

T_INLINE void CColliderSphere::SetRadius(f32 a_fRadius)
{
	this->m_fRadius = a_fRadius;
}

T_INLINE f32 CColliderSphere::GetRadius()
{
	return this->m_fRadius;
}

void CColliderSphere::SetScale(glm::vec3 a_vScale)
{
	f32 fScale = 0;
	fScale = glm::max(a_vScale.x, a_vScale.y);
	fScale = glm::max(fScale, a_vScale.z);
	this->m_fRadius *= fScale;
}

