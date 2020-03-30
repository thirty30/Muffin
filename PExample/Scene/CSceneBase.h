#pragma once

class CSceneBase
{
private:
	n32 m_nSceneID;
	tstring m_strSceneName;

protected:
	CGUIDMaker m_GUIDMaker;
	hash_map<u64, CGameObject*> m_mapID2GameObj;

public:
	CSceneBase(n32 a_nSceneID);
	virtual ~CSceneBase();

public:
	virtual tbool Init() T_PURE;
	virtual tbool LoadScene() T_PURE;
	virtual void ReleaseScene() T_PURE;
	virtual void Clear() T_PURE;
	virtual void Loop() T_PURE;

public:
	T_INLINE u64 CreateGUID();
	T_INLINE void AddGameObjet(CGameObject* a_pGameObject);
	tbool LoadSceneFile(const tcchar* a_strFileName);
	tbool LoadSceneGameObject(const rapidjson::Value::ConstObject& a_rNode);
};
