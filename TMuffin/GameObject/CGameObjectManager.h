#pragma once

class CGameObjectManager
{
public:
	hash_map<u64, CGameObject*> m_mapID2GameObj;

public:
	CGameObjectManager();
	~CGameObjectManager();

	void AddObject(CGameObject* a_pGameObject);
	CGameObject* FindObject(u64 a_nGUID);
	void RemoveObject(CGameObject* a_pGameObject);
};

