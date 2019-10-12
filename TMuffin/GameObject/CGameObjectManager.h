#pragma once

class CGameObjectManager : public CSingleton<CGameObjectManager>
{
public:
	u64 m_nGUIDGen;
	hash_map<n32, CGameObject*> m_mapID2GameObj;

public:
	CGameObjectManager();
	~CGameObjectManager();

	tbool AddGameObject(CGameObject* a_pGameObject);
	CGameObject* FindGameObjectByID(n32 a_nID);
	void DeleteGameObject(CGameObject* a_pGameObject);
	void RefreshColliderPosition();
};

