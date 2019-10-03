#include "pch.h"

T_IMPLEMENT_SINGLETON(CGameObjectManager)

tbool CGameObjectManager::RegisterGameObject(CGameObject* a_pGameObject)
{
	this->m_vList.push_back(a_pGameObject);
	return true;
}


