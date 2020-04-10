#include "Engine.h"
#include "Window/CWindow.h"
#include "GameObject/CGameObjectManager.h"
#include "ExportFunction.h"
#include "AssetsLoader/CAssetsPool.h"

//components
#include "Particle/CParticleEmitter.h"
#include "Light/CLight.h"
#include "Graphics/FBO/CFBOComponent.h"
#include "Graphics/CGraphicsComponent.h"
#include "Graphics/Stencil/CStencilComponent.h"
#include "Camera/CCamera.h"
#include "Animation/CAnimation.h"
#include "Physics/CPhysicsComponent.h"
#include "Audio/CAudioManager.h"

CMuffin MUFFIN;

tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	if (MUFFIN.GetWindow()->InitWindow(a_nWinWidth, a_nWinHigh, a_strWinName) == false)
	{
		return false;
	}
	MUFFIN.GetAssetsPoolMgr()->CreateWorker(3);
	MUFFIN.GetAudioMgr()->Init();
	return true;
}

void MuffinMainLoop()
{
	while (MUFFIN.IsRun() == true)
	{
		MUFFIN.Tick();

		glfwPollEvents();

		// GameLogic loop
		{
			MUFFIN.GetGameObjectMgr()->Init();
			MUFFIN.GetGameObjectMgr()->Update();
			if (pExternalGameLogicCallBack != NULL)
			{
				pExternalGameLogicCallBack();
			}
			MUFFIN.GetAssetsPoolMgr()->Update();
			MUFFIN.GetAssetsPoolMgr()->UpdateCallBack();
		}

		// Physics loop
		{
			//MUFFIN.GetPhysicsWorld()->PhysicsLoop(MUFFIN.GetDeltaFrameTime());
			MUFFIN.GetPhysicsWorld()->PhysicsLoop(0.02f);
			if (pExternalPhysicsCallBack != NULL) 
			{
				pExternalPhysicsCallBack(); 
			}
		}

		// Rendering loop
		{
			MUFFIN.GetWindow()->DrawWindow();
		}
	}
}

void MuffinClear()
{
	MUFFIN.GetAudioMgr()->Clear();
	MUFFIN.GetWindow()->Clear();
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

CComponentBase* CreateComponent(CGameObject* a_pObj, tstring a_strClassName)
{
#define T_REGISTER_COM(v) if (a_strClassName == #v) { return a_pObj->AddComponent<v>(); }

	T_REGISTER_COM(CGraphicsComponent);
	T_REGISTER_COM(CPhysicsComponent);
	T_REGISTER_COM(CFBOComponent);
	T_REGISTER_COM(CStencilComponent);
	T_REGISTER_COM(CParticleEmitter);
	T_REGISTER_COM(CDirectionLight);
	T_REGISTER_COM(CPointLight);
	T_REGISTER_COM(CSpotLight);
	T_REGISTER_COM(CCamera);

#undef T_REGISTER_COM
	return NULL;
}








