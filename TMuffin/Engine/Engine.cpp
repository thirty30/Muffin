#include "pch.h"

CMuffin MUFFIN;

tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	if (MUFFIN.GetWindow()->InitWindow(a_nWinWidth, a_nWinHigh, a_strWinName) == false)
	{
		return false;
	}
	return true;
}

void MuffinClear()
{
	MUFFIN.GetWindow()->Clear();
}

void MuffinMainLoop()
{
	while (MUFFIN.IsRun() == true)
	{
		MUFFIN.Tick();

		glfwPollEvents();

		MuffinGameLogicLoop();

		MuffinPhysicsLoop();

		MuffinRenderingLoop();
	}
}

void MuffinPhysicsLoop()
{
	MUFFIN.GetPhysicsReactor()->PhysicsLoop();
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
	MUFFIN.GetParticleEmitterMgr()->Update();
	MUFFIN.GetWindow()->DrawWindow();
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


















