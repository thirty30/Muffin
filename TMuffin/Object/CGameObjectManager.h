#pragma once

class CGameObjectManager : public CSingleton<CGameObjectManager>
{
public:
	vector<CGameObject*> m_vList;

public:
	tbool RegisterGameObject(CGameObject* a_pGameObject);
};


