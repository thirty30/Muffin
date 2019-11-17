#pragma once

class CScene
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;
	u64 m_nGUIDIdx;
	hash_map<u64, CGameObject*> m_mapID2GameObj;
	CSkyBox* m_pSkyBox;

private:
	u64 GenGUID();

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();
	void Loop();

	CCamera* GetCamera() { return this->m_pCamera; }
	void AddGameObject();

public:	
	CParticleEmitter* pTempParticle;
	f64 m_fLastTime;
};


