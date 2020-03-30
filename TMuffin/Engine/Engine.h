#pragma once
#include "TMuffinSysInclude.h"
#include "Muffin.h"
#include "Component/CComponentBase.h"

///////////////////-------------global variables stat-------------///////////////////

extern CMuffin MUFFIN;

///////////////////-------------global variables end-------------///////////////////

extern tbool MuffinInit(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
extern void MuffinMainLoop();
extern void MuffinClear();

extern void GLFWErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc);
extern void KeyCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
extern void MouseCallBack(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nAction, n32 a_nMods);
extern void CursorCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);
extern void ScrollCallBack(GLFWwindow* a_pWindow, f64 a_fX, f64 a_fY);

T_DLL_EXPORT extern CComponentBase* CreateComponent(CGameObject* a_pObj, tstring a_strClassName);