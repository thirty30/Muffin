#pragma once

T_DLL_EXPORT tbool TMuffin_Initialize(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
T_DLL_EXPORT void TMuffin_Loop();
T_DLL_EXPORT void TMuffin_Clear();

//------------Register call back function start------------//
extern MuffinKeyCallBack pExternalKeyCallBack;
extern MuffinMouseCallBack pExternalMouseCallBack;
extern MuffinCursorCallBack pExternalCursorCallBack;
extern MuffinPhysicsCallBack pExternalPhysicsCallBack;
extern MuffinGameLogicCallBack pExternalGameLogicCallBack;

T_DLL_EXPORT void TMuffin_RegisterKeyCallback(MuffinKeyCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterMouseCallback(MuffinMouseCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterCursorCallback(MuffinCursorCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterPhysicsCallBack(MuffinPhysicsCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterGameLogicCallBack(MuffinGameLogicCallBack a_func);


//------------Register call back function end------------//


T_DLL_EXPORT void TMuffin_AddGameObjects(CGameObject* a_pGameObject);
T_DLL_EXPORT void TMuffin_AddCamera(CCamera* a_pCamera);






