#include "CTransform.h"

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

void CTransform::SetRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation = glm::quat(vAngle);
}

void CTransform::SetRotation(glm::quat a_quat)
{
	this->m_qRotation = a_quat;
}

void CTransform::UpdateRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation *= glm::quat(vAngle);
}

void CTransform::UpdateRotation(glm::quat a_quat)
{
	this->m_qRotation *= a_quat;
}

glm::vec3 CTransform::GetEulerAngle()
{
	return glm::eulerAngles(this->m_qRotation);
}
