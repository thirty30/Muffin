#include "pch.h"

CGameObjectManager::CGameObjectManager()
{
	this->m_mapID2GameObj.clear();
}

CGameObjectManager::~CGameObjectManager()
{

}

tbool CGameObjectManager::AddGameObject(CGameObject* a_pGameObject)
{
	u64 nGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_GAME_OBJECT);
	a_pGameObject->m_nMuffinEngineGUID = nGUID;
	this->m_mapID2GameObj[nGUID] = a_pGameObject;
	return true;
}

CGameObject* CGameObjectManager::FindGameObjectByID(u64 a_nGUID)
{
	hash_map<u64, CGameObject*>::iterator iter = this->m_mapID2GameObj.find(a_nGUID);
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
	hash_map<u64, CGameObject*>::iterator iter = this->m_mapID2GameObj.begin();
	for (; iter != this->m_mapID2GameObj.end(); iter++)
	{
		CGameObject* pObj = iter->second;
		if (pObj != NULL)
		{
			pObj->RefreshColliderPostion();
		}
	}
}

