#include "pch.h"

T_IMPLEMENT_SINGLETON(CGameObjectManager)

CGameObjectManager::CGameObjectManager()
{
	this->m_nGUIDGen = 0;
	this->m_mapID2GameObj.clear();
}

CGameObjectManager::~CGameObjectManager()
{

}

tbool CGameObjectManager::AddGameObject(CGameObject* a_pGameObject)
{
	u64 nGUID = ++this->m_nGUIDGen;
	a_pGameObject->m_nMuffinEngineGUID = nGUID;
	if (this->FindGameObjectByID(nGUID) != NULL)
	{
		return false;
	}
	this->m_mapID2GameObj[nGUID] = a_pGameObject;
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

void CGameObjectManager::DeleteGameObject(CGameObject* a_pGameObject)
{
	u64 nGUID = a_pGameObject->m_nMuffinEngineGUID;
	if (this->FindGameObjectByID(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2GameObj.erase(nGUID);
}

void CGameObjectManager::RefreshColliderPosition()
{
	hash_map<n32, CGameObject*>::iterator iter = this->m_mapID2GameObj.begin();
	for (; iter != this->m_mapID2GameObj.end(); iter++)
	{
		CGameObject* pObj = iter->second;
		if (pObj != NULL)
		{
			pObj->RefreshColliderPostion();
		}
	}
}

