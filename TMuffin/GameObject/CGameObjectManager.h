#pragma once

class CGameObjectManager
{
public:
	hash_map<u64, CGameObject*> m_mapID2GameObj;

public:
	CGameObjectManager();
	~CGameObjectManager();

	tbool AddGameObject(CGameObject* a_pGameObject);
	CGameObject* FindGameObjectByID(u64 a_nGUID);
	void DeleteGameObject(CGameObject* a_pGameObject);
	void RefreshColliderPosition();
};

