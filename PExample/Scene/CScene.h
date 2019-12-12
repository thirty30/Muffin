#pragma once

class CScene
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;
	CShipControl* m_pShipControl;
	n32 m_nGUIDIdx;
	hash_map<u64, CActor*> m_mapID2Actor;
	CSkyBox* m_pSkyBox;

private:
	n32 GenGUID();

public:
	lua_State* m_pLuaState;

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();
	void Loop();

	CCamera* GetCamera() { return this->m_pCamera; }
};


