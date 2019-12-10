#pragma once

extern "C" n32 CreateActor(lua_State * a_pL);
extern "C" n32 AddLineTweenMove(lua_State * a_pL);
extern "C" n32 AddLineTweenScale(lua_State * a_pL);
extern "C" n32 AddLineTweenRotation(lua_State * a_pL);
extern "C" n32 AddLineTweenCurve(lua_State * a_pL);
extern "C" n32 AddLineTweenFollow(lua_State * a_pL);
extern "C" n32 AddControl(lua_State * a_pL);
extern "C" n32 AddToLineTweenGroup(lua_State * a_pL);
extern "C" n32 LineTweenGroupFollow(lua_State * a_pL);
