#pragma once
#include "TMuffinSysInclude.h"

enum EShaderType
{
	E_SHADER_TYPE_UNKNOWN = 0,
	E_SHADER_TYPE_VERTEX,
	E_SHADER_TYPE_FRAGMENT,
};

enum ERenderMode
{
	E_RENDER_MODE_POINT,
	E_RENDER_MODE_LINE,
	E_RENDER_MODE_FILL
};

enum ELightType
{
	E_LIGHT_TYPE_INIT = 0,

	E_LIGHT_TYPE_DIRECTION,
	E_LIGHT_TYPE_POINT,
	E_LIGHT_TYPE_SPOT,
};

enum EGUIDType
{
	E_GUID_INIT = -1,

	E_GUID_GAMEOBJECT,			// game object

	E_GUID_MAX,
};

enum EParticleMode
{
	E_PARTICLE_MODE_UNKNOWN = 0,

	E_PARTICLE_MODE_NORMAL,
	E_PARTICLE_MODE_BILLBOARD,
};

enum ELineTweenType
{
	E_LINETWEEN_TYPE_INIT = 0,

	E_LINETWEEN_TYPE_MOVE_TO,
	E_LINETWEEN_TYPE_SCALE_TO,
	E_LINETWEEN_TYPE_ROTATE_TO,
	E_LINETWEEN_TYPE_CURVE,
	E_LINETWEEN_TYPE_FOLLOW,
};


enum EMaterialParamVariableType
{
	E_MPVT_UNKNOWN = 0,

	E_MPVT_TEXTURE,
	E_MPVT_FBO_TEXTURE,

	E_MPVT_INT,
	E_MPVT_INT_VEC2,
	E_MPVT_INT_VEC3,
	E_MPVT_INT_VEC4,

	E_MPVT_FLOAT,
	E_MPVT_FLOAT_VEC2,
	E_MPVT_FLOAT_VEC3,
	E_MPVT_FLOAT_VEC4,
};

typedef void (*MuffinKeyCallBack)(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinMouseCallBack)(n32 a_nKey, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinCursorCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinScrollCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinPhysicsCallBack)();
typedef void (*MuffinGameLogicCallBack)();

#define GRAVITY_ACCELERATION glm::vec3(0.0f, -9.8f, 0.0f);



