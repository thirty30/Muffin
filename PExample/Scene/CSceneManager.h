#pragma once

class CSceneManager : public CSingleton<CSceneManager>
{
private:
	vector<CSceneBase*> m_vecScene;
	n32 m_nCurSceneID;
	CGUIDMaker m_GUIDMaker;

public:
	CSceneManager();
	~CSceneManager();

	tbool Init();
	void Clear();

	void AddScene(CSceneBase* a_pScene);
	CSceneBase* GetCurrentScene();
	void SwitchScene(n32 a_nSceneID);
	void Loop();
};
