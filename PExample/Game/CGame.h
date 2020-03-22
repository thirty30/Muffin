#pragma once

class CGame : public CSingleton<CGame>
{
private:
	n32 m_nScreenWidth;
	n32 m_nScreenHigh;
	tstring m_strWindowName;
	CSceneManager* m_pSceneManager;
	EGameStatus m_eGameStatus;
	CRofManager* m_pRofManager;
	CControlManager* m_pControlManager;

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
	T_INLINE n32 GetScreenWidth() { return this->m_nScreenWidth; }
	T_INLINE n32 GetScreenHigh() { return this->m_nScreenHigh; }
	T_INLINE CRofManager* GetRofManager() { return this->m_pRofManager; }
	T_INLINE CControlManager* GetControlManager() { return this->m_pControlManager; }
	void PhysicsLoop();
	void GameLogicLoop();
};



