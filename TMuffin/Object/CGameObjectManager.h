#pragma once

class CGameObjectManager : public CSingleton<CGameObjectManager>
{
public:
	hash_map<n32, CGameObject*> m_mapID2GameObj;

public:
	CGameObjectManager();
	~CGameObjectManager();

	tbool AddGameObject(u64 a_nGUID, CGameObject* a_pGameObject);
	CGameObject* FindGameObjectByID(n32 a_nID);
};

