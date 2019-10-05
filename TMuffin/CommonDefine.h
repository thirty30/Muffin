#pragma once

enum EShaderType
{
	E_SHADER_TYPE_UNKNOWN = 0,
	E_SHADER_TYPE_VERTEX,
	E_SHADER_TYPE_FRAGMENT,
};

enum ELightType
{
	E_LIGHT_TYPE_INIT = 0,

	E_LIGHT_TYPE_DIRECTION,
	E_LIGHT_TYPE_SPOT,
};


typedef void (*MuffinKeyCallBack)(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinMouseCallBack)(n32 a_nKey, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinCursorCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinPhysicsCallBack)();
typedef void (*MuffinGameLogicCallBack)();


