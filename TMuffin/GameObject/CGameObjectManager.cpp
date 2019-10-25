#include "pch.h"

CGameObjectManager::CGameObjectManager()
{
	this->m_mapID2GameObj.clear();
}

CGameObjectManager::~CGameObjectManager()
{

}

void CGameObjectManager::AddObject(CGameObject* a_pGameObject)
{
	this->m_mapID2GameObj[a_pGameObject->m_nMuffinGameObectGUID] = a_pGameObject;
}

CGameObject* CGameObjectManager::FindObject(u64 a_nGUID)
{
	hash_map<u64, CGameObject*>::iterator iter = this->m_mapID2GameObj.find(a_nGUID);
	if (iter == this->m_mapID2GameObj.end())
	{
		return NULL;
	}
	return iter->second;
}

void CGameObjectManager::RemoveObject(CGameObject* a_pGameObject)
{
	u64 nGUID = a_pGameObject->m_nMuffinGameObectGUID;
	if (this->FindObject(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2GameObj.erase(nGUID);
}


