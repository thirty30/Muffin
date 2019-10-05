#include "pch.h"

CWindow* pMuffinWindow = NULL;
CGameObjectManager* pMuffinGameObjectManager = NULL;
CCameraManager* pMuffinCameraManager = NULL;
MuffinKeyCallBack pMuffinKeyCallBack = NULL;
MuffinMouseCallBack pMuffinMouseCallBack = NULL;
MuffinCursorCallBack pMuffinCursorCallBack = NULL;
MuffinLogicCallBack pMuffinLogicCallBack = NULL;
tbool bMuffinRun = false;

tbool InitMuffin()
{
	pMuffinGameObjectManager = new CGameObjectManager();
	pMuffinCameraManager = new CCameraManager();
	pMuffinWindow = new CWindow();
	bMuffinRun = true;
	return true;
}

tbool InitMuffinWindow(n32 a_nWinWidth, n32 a_nWinHigh, tstring a_strWinName)
{
	if (pMuffinWindow->InitWindow(a_nWinWidth, a_nWinHigh, a_strWinName) == false)
	{
		return false;
	}
	
	return true;
}

void ClearMuffin()
{
	if (pMuffinGameObjectManager != NULL)
	{
		delete pMuffinGameObjectManager;
		pMuffinGameObjectManager = NULL;
	}
	if (pMuffinWindow != NULL)
	{
		pMuffinWindow->Clear();
		delete pMuffinWindow;
		pMuffinWindow = NULL;
	}
	if (pMuffinCameraManager != NULL)
	{
		delete pMuffinCameraManager;
		pMuffinCameraManager = NULL;
	}
}

void LoopMuffin()
{
	while (!CWindow::GetSingleton().WindowShouldClose())
	{
		//Physics
		LoopMuffinPhysics();
		
		glfwPollEvents();

		//Game logic
		LoopMuffinLogic();

		//Graphics
		LoopMuffinGraphics();
	}
}


void LoopMuffinPhysics()
{

}

void LoopMuffinGraphics()
{
	pMuffinWindow->DrawWindow();
}

void LoopMuffinLogic()
{
	if (pMuffinLogicCallBack != NULL)
	{
		pMuffinLogicCallBack();
	}
}

/////////////////////////////////////////

void TMuffin_RegisterKeyCallback(MuffinKeyCallBack a_func)
{
	pMuffinKeyCallBack = a_func;
}

void TMuffin_RegisterMouseCallback(MuffinMouseCallBack a_func)
{
	pMuffinMouseCallBack = a_func;
}

void TMuffin_RegisterCursorCallback(MuffinCursorCallBack a_func)
{
	pMuffinCursorCallBack = a_func;
}

void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	if (pMuffinKeyCallBack != NULL)
	{
		pMuffinKeyCallBack(a_nKey, a_nScancode, a_nAction, a_nMods);
	}
}
void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	if (pMuffinMouseCallBack != NULL)
	{
		pMuffinMouseCallBack(a_nKey, a_nAction, a_nMods);
	}
}
void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY)
{
	if (pMuffinCursorCallBack != NULL)
	{
		pMuffinCursorCallBack(a_fX, a_fY);
	}
}

void TMuffin_AddGameObjects(CGameObject* a_pGameObject)
{
	pMuffinGameObjectManager->RegisterGameObject(a_pGameObject);
}

void TMuffin_AddCamera(CCamera* a_pCamera)
{
	pMuffinCameraManager->AddCamera(a_pCamera);
}

void TMuffin_RegisterLogicCallBack(MuffinLogicCallBack a_func)
{
	pMuffinLogicCallBack = a_func;
}


