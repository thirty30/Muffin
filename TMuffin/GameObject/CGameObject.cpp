#include "pch.h"
#include "./CGameObject.h"

CGameObject::CGameObject()
{
	this->m_nMuffinGameObectGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_GAME_OBJECT);
	this->m_bEnable = true;
	this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);

	MUFFIN.GetGameObjectMgr()->AddObject(this);
}

CGameObject::~CGameObject()
{

}
