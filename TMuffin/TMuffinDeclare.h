#pragma once

typedef void (*MuffinKeyCallBack)(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinMouseCallBack)(n32 a_nKey, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinCursorCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinLogicCallBack)();


extern CWindow* pMuffinWindow;
extern CGameObjectManager* pMuffinGameObjectManager;
extern CCameraManager* pMuffinCameraManager;
extern MuffinKeyCallBack pMuffinKeyCallBack;
extern MuffinMouseCallBack pMuffinMouseCallBack;
extern MuffinCursorCallBack pMuffinCursorCallBack;
extern MuffinLogicCallBack pMuffinLogicCallBack;
extern tbool bMuffinRun;

T_DLL_EXPORT tbool InitMuffin();
T_DLL_EXPORT tbool InitMuffinWindow(n32 a_nWinWidth, n32 a_nWinHigh, tstring a_strWinName);
T_DLL_EXPORT void ClearMuffin();
T_DLL_EXPORT void LoopMuffin();

T_DLL_EXPORT void TMuffin_AddGameObjects(CGameObject* a_pGameObject);
T_DLL_EXPORT void TMuffin_AddCamera(CCamera* a_pCamera);
T_DLL_EXPORT void TMuffin_RegisterKeyCallback(MuffinKeyCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterMouseCallback(MuffinMouseCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterCursorCallback(MuffinCursorCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterLogicCallBack(MuffinLogicCallBack a_func);

/////////////////////////////////////////////
void LoopMuffinPhysics();
void LoopMuffinGraphics();
void LoopMuffinLogic();
void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods);
void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);

