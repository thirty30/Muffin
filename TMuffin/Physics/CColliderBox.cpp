#include "pch.h"

CColliderBox::CColliderBox() : CColliderBase(E_COLLIDER_TYPE_BOX)
{
	this->m_vSize = glm::vec3(1.0f, 1.0f, 1.0f);
}

CColliderBox::~CColliderBox()
{

}

void CColliderBox::SetScale(glm::vec3 a_vScale)
{
	this->m_vSize *= a_vScale;
}

T_INLINE glm::vec3 CColliderBox::GetMinPoint()
{
	return glm::vec3(this->m_vCenter.x - this->m_vSize.x, this->m_vCenter.y - this->m_vSize.y, this->m_vCenter.z - this->m_vSize.z);
}

T_INLINE glm::vec3 CColliderBox::GetMaxPoint()
{
	return glm::vec3(this->m_vCenter.x + this->m_vSize.x, this->m_vCenter.y + this->m_vSize.y, this->m_vCenter.z + this->m_vSize.z);
}

T_INLINE void CColliderBox::SetSize(glm::vec3 a_vSize)
{
	this->m_vSize = a_vSize;
}
