#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CGame)

CGame::CGame()
{
	this->m_nScreenWidth = 1600;
	this->m_nScreenHigh = 900;
	this->m_strWindowName = "pExample";
	this->m_pResManager = NULL;
	this->m_pShaderMgr = NULL;
	this->m_pScene = NULL;
	this->m_eGameStatus = E_GAME_STATUS_INIT;
}

CGame::~CGame()
{

}

tbool CGame::InitGame()
{
	TMuffin_RegisterKeyCallback(ControlKeyEvent);
	TMuffin_RegisterMouseCallback(ControlMouseEvent);
	TMuffin_RegisterCursorCallback(ControlCursorEvent);
	TMuffin_RegisterPhysicsCallBack(CGame::PhysicsCallBack);
	TMuffin_RegisterGameLogicCallBack(CGame::GameLogicCallBack);

	if (TMuffin_Initialize(this->m_nScreenWidth, this->m_nScreenHigh, this->m_strWindowName.c_str()) == false)
	{
		return 0;
	}

	this->m_pResManager = new CResourceManager();
	this->m_pResManager->Init();

	this->m_pShaderMgr = new CShaderManager();
	if (this->m_pShaderMgr->Init() == false)
	{
		return false;
	}
	
	this->m_pScene = new CScene();
	if (m_pScene->Init() == false)
	{
		return false;
	}
	return true;
}

void CGame::ClearGame()
{
	//release game data
	if (this->m_pResManager != NULL)
	{
		delete this->m_pResManager;
		this->m_pResManager = NULL;
	}
	if (this->m_pShaderMgr != NULL)
	{
		this->m_pShaderMgr->Clear();
		delete this->m_pShaderMgr;
		this->m_pShaderMgr = NULL;
	}
	if (this->m_pScene != NULL)
	{
		this->m_pScene->Clear();
		delete this->m_pScene;
		this->m_pScene = NULL;
	}

	//release engine
	TMuffin_Clear();
}

void CGame::LoopGame()
{
	TMuffin_Loop();
}

void CGame::SetScreenSize(n32 a_nWidth, n32 a_nHigh)
{
	this->m_nScreenWidth = a_nWidth;
	this->m_nScreenHigh = a_nHigh;
}

void CGame::PhysicsLoop()
{

}

void CGame::GameLogicLoop()
{
	if (this->m_eGameStatus == E_GAME_STATUS_INIT)
	{
		this->m_eGameStatus = E_GAME_STATUS_LOAD_SCENE_START;
	}
	else if (this->m_eGameStatus == E_GAME_STATUS_LOAD_SCENE_START)
	{
		this->m_pScene->LoadScene();
		this->m_eGameStatus = E_GAME_STATUS_LOAD_SCENE_FINISH;
	}
	else if (this->m_eGameStatus == E_GAME_STATUS_LOAD_SCENE_FINISH)
	{

	}
}


