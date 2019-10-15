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

tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
void MuffinClear();

void MuffinMainLoop();
void MuffinPhysicsLoop();
void MuffinGameLogicLoop();
void MuffinRenderingLoop();

void GLFWErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc);
void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods);
void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);
void ScrollCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);


