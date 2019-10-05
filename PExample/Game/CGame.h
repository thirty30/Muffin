#pragma once

class CGame : public CSingleton<CGame>
{
private:
	n32 m_nScreenWidth;
	n32 m_nScreenHigh;
	tstring m_strWindowName;
	CShaderManager* m_pShaderMgr;
	CScene* m_pScene;

public:
	static void PhysicsCallBack();
	static void GameLogicCallBack();
	
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
};



