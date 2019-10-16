#include "pch.h"

///////////////////-------------global variables stat-------------///////////////////
CWindow* g_pMuffinWindow = NULL;
CGameObjectManager* g_pMuffinGameObjectManager = NULL;
CCameraManager* g_pMuffinCameraManager = NULL;
CObjectRenderer* g_pObjectRenderer = NULL;
CObjectPhysics* g_pObjectPhysics = NULL;
CLightManager* g_pLightManager = NULL;
f64 g_fNowFrameTime = 0;
///////////////////-------------global variables end-------------///////////////////

tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	g_pMuffinGameObjectManager = new CGameObjectManager();

	g_pMuffinCameraManager = new CCameraManager();

	g_pObjectRenderer = new CObjectRenderer();

	g_pObjectPhysics = new CObjectPhysics();
	g_pObjectPhysics->Init();

	g_pLightManager = new CLightManager();

	g_pMuffinWindow = new CWindow();
	if (g_pMuffinWindow->InitWindow(a_nWinWidth, a_nWinHigh, a_strWinName) == false)
	{
		return false;
	}
	return true;
}

void MuffinClear()
{
	if (g_pMuffinGameObjectManager != NULL)
	{
		delete g_pMuffinGameObjectManager;
		g_pMuffinGameObjectManager = NULL;
	}
	if (g_pMuffinCameraManager != NULL)
	{
		delete g_pMuffinCameraManager;
		g_pMuffinCameraManager = NULL;
	}
	if (g_pObjectPhysics != NULL)
	{
		delete g_pObjectPhysics;
		g_pObjectPhysics = NULL;
	}
	if (g_pObjectRenderer != NULL)
	{
		delete g_pObjectRenderer;
		g_pObjectRenderer = NULL;
	}
	if (g_pLightManager != NULL)
	{
		delete g_pLightManager;
		g_pLightManager = NULL;
	}
	if (g_pMuffinWindow != NULL)
	{
		g_pMuffinWindow->Clear();
		delete g_pMuffinWindow;
		g_pMuffinWindow = NULL;
	}
}

void MuffinMainLoop()
{
	while (g_pMuffinWindow->WindowShouldClose() == false)
	{
		g_fNowFrameTime = glfwGetTime();

		glfwPollEvents();

		MuffinGameLogicLoop();

		MuffinPhysicsLoop();

		MuffinRenderingLoop();
	}
}

void MuffinPhysicsLoop()
{
	if (pExternalPhysicsCallBack != NULL)
	{
		pExternalPhysicsCallBack();
	}
	g_pObjectPhysics->PhysicsObjects(0.01f);
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
	g_pMuffinWindow->DrawWindow();
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
void ScrollCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY)
{
	if (pExternalScrollCallBack != NULL)
	{
		pExternalScrollCallBack(a_fX, a_fY);
	}
}


















