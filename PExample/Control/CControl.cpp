#include "stdafx.h"

void ControlKeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	CCameraControl::GetSingleton().CameraControlKeyPress(a_nKey, a_nScancode, a_nAction, a_nMods);
	CShipControl::GetSingleton().ControlKeyPress(a_nKey, a_nScancode, a_nAction, a_nMods);
}

void ControlMouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	CCameraControl::GetSingleton().CameraControlMousePress(a_nKey, a_nAction, a_nMods);
	CShipControl::GetSingleton().ControlMousePress(a_nKey, a_nAction, a_nMods);
}

void ControlCursorEvent(f64 a_fX, f64 a_fY)
{
	CCameraControl::GetSingleton().CameraControlCursor(a_fX, a_fY);
	CShipControl::GetSingleton().ControlCursor(a_fX, a_fY);
}

void ControlScrollEvent(f64 a_fX, f64 a_fY)
{
	CCameraControl::GetSingleton().CameraControlScroll(a_fX, a_fY);
}
