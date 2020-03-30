#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CGame)

CGame::CGame()
{
	this->m_nScreenWidth = 1600;
	this->m_nScreenHigh = 900;
	this->m_strWindowName = "pExample";
	this->m_pSceneManager = NULL;
	this->m_pRofManager = NULL;
	this->m_eGameStatus = E_GAME_STATUS_INIT;
}

CGame::~CGame()
{
	this->ClearGame();
}

tbool CGame::InitGame()
{
	TMuffin_RegisterKeyCallback(ControlKeyEvent);
	TMuffin_RegisterMouseCallback(ControlMouseEvent);
	TMuffin_RegisterCursorCallback(ControlCursorEvent);
	TMuffin_RegisterScrollCallback(ControlScrollEvent);
	TMuffin_RegisterPhysicsCallBack(CGame::PhysicsCallBack);
	TMuffin_RegisterGameLogicCallBack(CGame::GameLogicCallBack);
	TMuffin_RegisterComponent(CreateLogicComponent);
	
	if (TMuffin_Initialize(this->m_nScreenWidth, this->m_nScreenHigh, this->m_strWindowName.c_str()) == false)
	{
		return 0;
	}

	this->m_pRofManager = new CRofManager();
	if (this->m_pRofManager->Init("../Assets/Rof/Binary/") == false)
	{
		return false;
	}
	
	this->m_pSceneManager = new CSceneManager();
	if (this->m_pSceneManager->Init() == false)
	{
		return false;
	}

	this->m_pControlManager = new CControlManager();

	return true;
}

void CGame::ClearGame()
{
	//release game data
	if (this->m_pRofManager != NULL)
	{
		delete this->m_pRofManager;
		this->m_pRofManager = NULL;
	}
	if (this->m_pSceneManager != NULL)
	{
		this->m_pSceneManager->Clear();
		delete this->m_pSceneManager;
		this->m_pSceneManager = NULL;
	}
	if (this->m_pControlManager != NULL)
	{
		delete this->m_pControlManager;
		this->m_pControlManager = NULL;
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
		this->m_pSceneManager->SwitchScene(0);
		this->m_eGameStatus = E_GAME_STATUS_LOAD_SCENE_FINISH;
	}
	else if (this->m_eGameStatus == E_GAME_STATUS_LOAD_SCENE_FINISH)
	{
		this->m_pSceneManager->Loop();
	}
}


