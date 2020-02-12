#include "CTransform.h"

CTransform::CTransform()
{
	this->m_vPosition = glm::vec3(0, 0, 0);
	this->m_qRotation = glm::quat(0, 0, 0, 0);
	this->m_vScale = glm::vec3(1, 1, 1);
}

CTransform::~CTransform()
{
}

void CTransform::SetRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle = glm::radians(a_vEulerAngle);
	this->m_qRotation = glm::quat(vAngle);
}

void CTransform::SetRotation(glm::quat a_qQuaternion)
{
	this->m_qRotation = a_qQuaternion;
}

void CTransform::UpdateRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle = glm::radians(a_vEulerAngle);
	this->m_qRotation *= glm::quat(vAngle);
}

void CTransform::UpdateRotation(glm::quat a_qQuaternion)
{
	this->m_qRotation *= a_qQuaternion;
}

glm::vec3 CTransform::GetEulerAngle()
{
	return glm::eulerAngles(this->m_qRotation);
}
