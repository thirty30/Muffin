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

void CTransform::LookAt(glm::vec3 a_vTarget)
{
	glm::vec3 v1 = glm::vec3(0, 0, 1);
	glm::vec3 v2 = glm::normalize(a_vTarget);
	glm::quat qAngle = glm::rotation(v1, v2);
	this->SetRotation(qAngle);
}
