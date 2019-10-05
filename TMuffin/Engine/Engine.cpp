#include "pch.h"

///////////////////-------------global variables stat-------------///////////////////
CWindow* pMuffinWindow = NULL;
CGameObjectManager* pMuffinGameObjectManager = NULL;
CCameraManager* pMuffinCameraManager = NULL;
CObjectRenderer* pObjectRenderer = NULL;
///////////////////-------------global variables end-------------///////////////////

tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	pMuffinGameObjectManager = new CGameObjectManager();
	pMuffinCameraManager = new CCameraManager();
	pObjectRenderer = new CObjectRenderer();
	pMuffinWindow = new CWindow();
	if (pMuffinWindow->InitWindow(a_nWinWidth, a_nWinHigh, a_strWinName) == false)
	{
		return false;
	}
	return true;
}

void MuffinClear()
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

void MuffinMainLoop()
{
	while (pMuffinWindow->WindowShouldClose() == false)
	{
		MuffinPhysicsLoop();

		glfwPollEvents();

		MuffinGameLogicLoop();

		MuffinRenderingLoop();
	}
}

void MuffinPhysicsLoop()
{
	if (pExternalPhysicsCallBack != NULL)
	{
		pExternalPhysicsCallBack();
	}
}

void MuffinGameLogicLoop()
{
	if (pExternalGameLogicCallBack != NULL)
	{
		pExternalGameLogicCallBack();
	}
}

void MuffinRenderingLoop()
{
	pMuffinWindow->DrawWindow();
}

void GLFWErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc)
{
	printf("glfw error! error code: %d, error: %s", a_nErrorCode, a_strDesc);
}

void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	if (pExternalKeyCallBack != NULL)
	{
		pExternalKeyCallBack(a_nKey, a_nScancode, a_nAction, a_nMods);
	}
}
void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	if (pExternalMouseCallBack != NULL)
	{
		pExternalMouseCallBack(a_nKey, a_nAction, a_nMods);
	}
}
void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY)
{
	if (pExternalCursorCallBack != NULL)
	{
		pExternalCursorCallBack(a_fX, a_fY);
	}
}

















