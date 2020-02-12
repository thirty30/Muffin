#pragma once

class CSceneBase
{
private:
	n32 m_nSceneID;

protected:
	CGUIDMaker m_GUIDMaker;
	hash_map<u64, CGameObject*> m_mapID2GameObj;

public:
	CSceneBase(n32 a_nSceneID) : 
		m_nSceneID(a_nSceneID),
		m_GUIDMaker(1)
	{
		this->m_mapID2GameObj.clear();
	}
	virtual ~CSceneBase() 
	{
		for (auto iter : this->m_mapID2GameObj)
		{
			delete iter.second;
		}
		this->m_mapID2GameObj.clear();
	}

public:
	virtual tbool Init() T_PURE;
	virtual tbool LoadScene() T_PURE;
	virtual void ReleaseScene() T_PURE;
	virtual void Clear() T_PURE;
	virtual void Loop() T_PURE;

public:
	u64 CreateGUID() { return this->m_GUIDMaker.GenerateGUID(0); }
	void AddGameObjet(CGameObject* a_pGameObject)
	{
		u64 nGUID = a_pGameObject->GetGameObjectID();
		this->m_mapID2GameObj[nGUID] = a_pGameObject;
	}
};
