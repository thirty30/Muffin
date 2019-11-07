#include "pch.h"

CColliderPlane::CColliderPlane() : CColliderBase(E_COLLIDER_TYPE_PLANE)
{
	this->m_eAxis = E_PLANE_COLLIDER_AXIS_INIT;
}

CColliderPlane::~CColliderPlane()
{

}

T_INLINE void CColliderPlane::SetAxis(EPLaneColliderAxis a_eValue)
{
	this->m_eAxis = a_eValue;
}

T_INLINE EPLaneColliderAxis CColliderPlane::GetAxis()
{
	return this->m_eAxis;
}

