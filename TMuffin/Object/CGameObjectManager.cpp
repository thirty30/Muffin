#include "pch.h"

T_IMPLEMENT_SINGLETON(CGameObjectManager)

CGameObjectManager::CGameObjectManager()
{
	this->m_mapID2GameObj.clear();
}

CGameObjectManager::~CGameObjectManager()
{

}

tbool CGameObjectManager::AddGameObject(u64 a_nGUID, CGameObject* a_pGameObject)
{
	if (this->FindGameObjectByID(a_nGUID) != NULL)
	{
		return false;
	}
	this->m_mapID2GameObj[a_nGUID] = a_pGameObject;
	return true;
}

CGameObject* CGameObjectManager::FindGameObjectByID(n32 a_nID)
{
	hash_map<n32, CGameObject*>::iterator iter = this->m_mapID2GameObj.find(a_nID);
	if (iter == this->m_mapID2GameObj.end())
	{
		return NULL;
	}
	return iter->second;
}

