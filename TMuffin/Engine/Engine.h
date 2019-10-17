#pragma once

///////////////////-------------global variables stat-------------///////////////////
extern CWindow* g_pMuffinWindow;
extern CGameObjectManager* g_pMuffinGameObjectManager;
extern CCameraManager* g_pMuffinCameraManager;
extern CObjectRenderer* g_pObjectRenderer;
extern CObjectPhysics* g_pObjectPhysics;
extern CLightManager* g_pLightManager;
extern f64 g_fNowFrameTime;
///////////////////-------------global variables end-------------///////////////////

extern tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
extern void MuffinClear();

extern void MuffinMainLoop();
extern void MuffinPhysicsLoop(f64 a_fFrameTime);
extern void MuffinGameLogicLoop(f64 a_fFrameTime);
extern void MuffinRenderingLoop(f64 a_fFrameTime);

extern void GLFWErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc);
extern void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
extern void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods);
extern void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);
extern void ScrollCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);


