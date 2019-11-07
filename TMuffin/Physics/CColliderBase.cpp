#include "pch.h"

CColliderBase::CColliderBase(EColliderType a_eColliderType)
{
	this->m_eColliderType = a_eColliderType;
	this->m_vCenter = glm::vec3(0, 0, 0);
	this->m_fElastic = 1.0f;
	this->m_bIsTrigger = false;
}


T_INLINE EColliderType CColliderBase::GetColliderType()
{
	return this->m_eColliderType;
}

T_INLINE void CColliderBase::SetCenter(glm::vec3 a_vPosition)
{
	this->m_vCenter = a_vPosition;
}

T_INLINE glm::vec3 CColliderBase::GetCenter()
{
	return this->m_vCenter;
}

T_INLINE void CColliderBase::SetTrigger(tbool a_bValue)
{
	this->m_bIsTrigger = a_bValue;
}

T_INLINE tbool CColliderBase::IsTrigger()
{
	return this->m_bIsTrigger;
}

T_INLINE void CColliderBase::SetElastic(f32 a_fElastic)
{
	this->m_fElastic = a_fElastic;
}

T_INLINE f32 CColliderBase::GetElastic()
{
	return this->m_fElastic;
}
