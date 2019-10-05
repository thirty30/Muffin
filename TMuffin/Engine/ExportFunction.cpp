#include "pch.h"

tbool TMuffin_Initialize(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	return MuffinInit(a_nWinWidth, a_nWinHigh, a_strWinName);
}
void TMuffin_Loop()
{
	MuffinMainLoop();
}
void TMuffin_Clear()
{
	MuffinClear();
}

#define TMUFFIN_REGISTER_CALLBACK(FUNC_NAME, FUNC_TYPE, FUNC_VARIABLE) FUNC_TYPE FUNC_VARIABLE = NULL; \
	void FUNC_NAME(FUNC_TYPE a_func) { FUNC_VARIABLE = a_func; }

TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterKeyCallback, MuffinKeyCallBack, pExternalKeyCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterMouseCallback, MuffinMouseCallBack, pExternalMouseCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterCursorCallback, MuffinCursorCallBack, pExternalCursorCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterPhysicsCallBack, MuffinPhysicsCallBack, pExternalGameLogicCallBack)
TMUFFIN_REGISTER_CALLBACK(TMuffin_RegisterGameLogicCallBack, MuffinGameLogicCallBack, pExternalPhysicsCallBack)



void TMuffin_AddGameObjects(CGameObject* a_pGameObject)
{
	pMuffinGameObjectManager->RegisterGameObject(a_pGameObject);
}
void TMuffin_AddCamera(CCamera* a_pCamera)
{
	pMuffinCameraManager->AddCamera(a_pCamera);



}