#include "pch.h"

CWindow* pMuffinWindow = NULL;
CGameObjectManager* pMuffinGameObjectManager = NULL;
CCameraManager* pMuffinCameraManager = NULL;

tbool InitMuffin()
{
	pMuffinGameObjectManager = new CGameObjectManager();
	pMuffinCameraManager = new CCameraManager();
	return true;
}

tbool InitMuffinWindow(n32 a_nWinWidth, n32 a_nWinHigh, tstring a_strWinName)
{
	pMuffinWindow = new CWindow(a_nWinWidth, a_nWinHigh, a_strWinName);
	if (pMuffinWindow->InitWindow() == false)
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
	}
	if (pMuffinWindow != NULL)
	{
		pMuffinWindow->Clear();
		delete pMuffinWindow;
	}
}

void LoopMuffin()
{
	LoopMuffinPhysics();
	LoopMuffinGraphics();
}

void TMuffin_AddGameObjects(CGameObject* a_pGameObject)
{
	pMuffinGameObjectManager->RegisterGameObject(a_pGameObject);
}

void TMuffin_AddCamera(CCamera* a_pCamera)
{
	pMuffinCameraManager->AddCamera(a_pCamera);
}

void LoopMuffinPhysics()
{

}

void LoopMuffinGraphics()
{
	pMuffinWindow->Loop();
}





