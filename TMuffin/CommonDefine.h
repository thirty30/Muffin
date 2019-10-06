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

enum ERenderMode
{
	E_RENDER_MODE_POINT,
	E_RENDER_MODE_LINE,
	E_RENDER_MODE_FILL
};

enum EPhysicsType
{
	E_PHYSICS_TYPE_INIT = 0,
	
	E_PHYSICS_TYPE_AABB,
	E_PHYSICS_TYPE_SPHERE,
	E_PHYSICS_TYPE_MESH,
};


typedef void (*MuffinKeyCallBack)(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinMouseCallBack)(n32 a_nKey, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinCursorCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinPhysicsCallBack)();
typedef void (*MuffinGameLogicCallBack)();


