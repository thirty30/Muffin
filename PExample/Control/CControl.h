#pragma once

void ControlKeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
void ControlMouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods);
void ControlCursorEvent(f64 a_fX, f64 a_fY);
void ControlScrollEvent(f64 a_fX, f64 a_fY);