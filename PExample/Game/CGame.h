#pragma once

class CGame : public CSingleton<CGame>
{
private:
	n32 m_nScreenWidth;
	n32 m_nScreenHigh;
	tstring m_strWindowName;
	CResourceLoader* m_pResourceLoader;
	CShaderManager* m_pShaderMgr;
	CScene* m_pScene;
	EGameStatus m_eGameStatus;

public:
	static void PhysicsCallBack() { CGame::GetSingleton().PhysicsLoop(); }
	static void GameLogicCallBack() { CGame::GetSingleton().GameLogicLoop(); }
	
public:
	CGame();
	~CGame();

	tbool InitGame();
	void ClearGame();
	void LoopGame();

	void SetScreenSize(n32 a_nWidth, n32 a_nHigh);
	inline n32 GetScreenWidth() { return this->m_nScreenWidth; }
	inline n32 GetScreenHigh() { return this->m_nScreenHigh; }
	CScene* GetCurrentScene() { return this->m_pScene; }
	CResourceLoader* GetResourceLoader() { return this->m_pResourceLoader; };
	void PhysicsLoop();
	void GameLogicLoop();
};



