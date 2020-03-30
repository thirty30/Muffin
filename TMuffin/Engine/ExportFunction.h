#pragma once
#include "TMuffinSysInclude.h"
#include "Component/CComponentBase.h"
#include "GameObject/CGameObject.h"

T_DLL_EXPORT tbool TMuffin_Initialize(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
T_DLL_EXPORT void TMuffin_Loop();
T_DLL_EXPORT void TMuffin_Clear();

//------------Register call back function start------------//
extern MuffinKeyCallBack pExternalKeyCallBack;
extern MuffinMouseCallBack pExternalMouseCallBack;
extern MuffinCursorCallBack pExternalCursorCallBack;
extern MuffinScrollCallBack pExternalScrollCallBack;
extern MuffinPhysicsCallBack pExternalPhysicsCallBack;
extern MuffinGameLogicCallBack pExternalGameLogicCallBack;

T_DLL_EXPORT void TMuffin_RegisterKeyCallback(MuffinKeyCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterMouseCallback(MuffinMouseCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterCursorCallback(MuffinCursorCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterScrollCallback(MuffinScrollCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterPhysicsCallBack(MuffinPhysicsCallBack a_func);
T_DLL_EXPORT void TMuffin_RegisterGameLogicCallBack(MuffinGameLogicCallBack a_func);


//------------Register call back function end------------//

T_DLL_EXPORT f64 TMuffin_GetNowFrameTime();
T_DLL_EXPORT f32 TMuffin_GetDeltaFrameTime();
T_DLL_EXPORT void TMuffin_SetSkyBox(const tcchar* a_strMeshFile,
	const tcchar* a_strVertexShader, const tcchar* a_strFragmentShader,
	const tcchar* a_strXTexture, const tcchar* a_strNegXTexture,
	const tcchar* a_strYTexture, const tcchar* a_strNegYTexture,
	const tcchar* a_strZTexture, const tcchar* a_strNegZTexture);


typedef CComponentBase* (*MuffinCreateComponent)(CGameObject* a_pObj, tstring a_strClassName);
extern MuffinCreateComponent pExternalCreateComponent;
T_DLL_EXPORT void TMuffin_RegisterComponent(MuffinCreateComponent a_fuc);