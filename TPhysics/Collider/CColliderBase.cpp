#include "CColliderBase.h"

CColliderBase::CColliderBase(EColliderType a_eColliderType)
{
	this->m_eColliderType = a_eColliderType;
	this->m_vCenter = glm::vec3(0, 0, 0);
	this->m_fElastic = 1.0f;
	this->m_bIsTrigger = false;
}

CColliderBase::~CColliderBase()
{

}

