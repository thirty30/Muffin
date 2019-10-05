#pragma once

///////////////////-------------global variables stat-------------///////////////////
extern CWindow* pMuffinWindow;
extern CGameObjectManager* pMuffinGameObjectManager;
extern CCameraManager* pMuffinCameraManager;
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


