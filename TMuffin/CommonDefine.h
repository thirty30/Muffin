#pragma once

enum EComponentType
{
	E_COMPONENT_INIT = 0,

	E_COMPONENT_MESH_RENDER,
	E_COMPONENT_RIGIDBODY,
	E_COMPONENT_PLANE_COLLIDER,
	E_COMPONENT_SPHERE_COLLIDER,
	E_COMPONENT_BOX_COLLIDER,
	E_COMPONENT_MESH_COLLIDER,

	E_COMPONENT_MAX,
};

enum EColliderType
{
	E_COLLIDER_TYPE_INVALID = -1,
	E_COLLIDER_TYPE_INIT = 0,

	E_COLLIDER_TYPE_PLANE,
	E_COLLIDER_TYPE_SPHERE,
	E_COLLIDER_TYPE_BOX,
	E_COLLIDER_TYPE_MESH,
	//E_COLLIDER_TYPE_CAPSULE,

	E_COLLIDER_TYPE_END,
};

enum EPLaneColliderAxis
{
	E_PLANE_COLLIDER_AXIS_INIT = 0,

	E_PLANE_COLLIDER_AXIS_X,
	E_PLANE_COLLIDER_AXIS_Y,
	E_PLANE_COLLIDER_AXIS_Z,
};


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
	E_LIGHT_TYPE_SPOT,
};

#define DEBUG_SPHERE_OBJECT_ID 10000000

typedef void (*MuffinKeyCallBack)(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinMouseCallBack)(n32 a_nKey, n32 a_nAction, n32 a_nMods);
typedef void (*MuffinCursorCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinScrollCallBack)(f64 a_fX, f64 a_fY);
typedef void (*MuffinPhysicsCallBack)();
typedef void (*MuffinGameLogicCallBack)();


