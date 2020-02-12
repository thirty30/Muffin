#pragma once
#include "TMuffinSysInclude.h"

class CGameObject;
class CGameObjectManager
{
public:
	TLinkedList<CGameObject*> m_listGameObject;
	hash_map<u64, TLinkedNode<CGameObject*>*> m_mapID2Node;

public:
	CGameObjectManager();
	~CGameObjectManager();

	void AddObject(CGameObject* a_pGameObject);
	CGameObject* FindObject(u64 a_nGUID);
	TLinkedNode<CGameObject*>* FindObjectNode(u64 a_nGUID);
	void RemoveObject(CGameObject* a_pGameObject);
	void Init();
	void Update();
};
