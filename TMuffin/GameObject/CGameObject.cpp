#include "pch.h"
#include "./CGameObject.h"

CGameObject::CGameObject()
{
	this->m_nMuffinGameObectGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_GAME_OBJECT);
	this->m_bEnable = true;
	this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_qRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

	MUFFIN.GetGameObjectMgr()->AddObject(this);
}

CGameObject::~CGameObject()
{

}

void CGameObject::SetRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation = glm::quat(vAngle);
}

void CGameObject::SetRotation(glm::quat a_quat)
{
	this->m_qRotation = a_quat;
}

void CGameObject::UpdateRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation *= glm::quat(vAngle);
}

void CGameObject::UpdateRotation(glm::quat a_quat)
{
	this->m_qRotation *= a_quat;
}

glm::vec3 CGameObject::GetEulerAngle()
{
	return glm::eulerAngles(this->m_qRotation);
}
