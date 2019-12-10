#include "stdafx.h"

n32 CreateActor(lua_State* a_pL)
{
	n32 nParmNum = lua_gettop(a_pL);
	f32 fX = lua_tonumber(a_pL, 1);
	f32 fY = lua_tonumber(a_pL, 2);
	f32 fZ = lua_tonumber(a_pL, 3);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->NewActor();
	pActor->m_vPosition = glm::vec3(fX, fY, fZ);
	lua_pushnumber(a_pL, pActor->m_nActorID);
	return 1;
}

n32 AddLineTweenMove(lua_State * a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);

	f32 fFromX = lua_tonumber(a_pL, 2);
	f32 fFromY = lua_tonumber(a_pL, 3);
	f32 fFromZ = lua_tonumber(a_pL, 4);

	f32 fToX = lua_tonumber(a_pL, 5);
	f32 fToY = lua_tonumber(a_pL, 6);
	f32 fToZ = lua_tonumber(a_pL, 7);

	f32 fVelocity = lua_tonumber(a_pL, 8);
	f32 fEaseTime = lua_tonumber(a_pL, 9);
	tbool bIsSerial = lua_toboolean(a_pL, 10);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	if (pActor == NULL)
	{
		return 0;
	}
	CLineTweenMove* pLineTween = NULL;
	if (bIsSerial == true)
	{
		pLineTween = (CLineTweenMove*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_MOVE_TO);
	}
	else
	{
		pLineTween = (CLineTweenMove*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_MOVE_TO);
	}
	
	pLineTween->Init(glm::vec3(fFromX, fFromY, fFromZ), glm::vec3(fToX, fToY, fToZ), fVelocity, fEaseTime);
	return 0;
}

n32 AddLineTweenScale(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);

	f32 fFromX = lua_tonumber(a_pL, 2);
	f32 fFromY = lua_tonumber(a_pL, 3);
	f32 fFromZ = lua_tonumber(a_pL, 4);

	f32 fToX = lua_tonumber(a_pL, 5);
	f32 fToY = lua_tonumber(a_pL, 6);
	f32 fToZ = lua_tonumber(a_pL, 7);

	f32 fTime = lua_tonumber(a_pL, 8);
	tbool bIsSerial = lua_toboolean(a_pL, 9);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	if (pActor == NULL)
	{
		return 0;
	}
	CLineTweenScale* pLineTween = NULL;
	if (bIsSerial == true)
	{
		pLineTween = (CLineTweenScale*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_SCALE_TO);
	}
	else
	{
		pLineTween = (CLineTweenScale*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_SCALE_TO);
	}
	
	pLineTween->Init(glm::vec3(fFromX, fFromY, fFromZ), glm::vec3(fToX, fToY, fToZ), fTime);

	return 0;
}

n32 AddLineTweenRotation(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);

	f32 fFromX = lua_tonumber(a_pL, 2);
	f32 fFromY = lua_tonumber(a_pL, 3);
	f32 fFromZ = lua_tonumber(a_pL, 4);

	f32 fToX = lua_tonumber(a_pL, 5);
	f32 fToY = lua_tonumber(a_pL, 6);
	f32 fToZ = lua_tonumber(a_pL, 7);

	f32 fTime = lua_tonumber(a_pL, 8);
	tbool bIsSerial = lua_toboolean(a_pL, 9);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	if (pActor == NULL)
	{
		return 0;
	}
	CLineTweenRotation* pLineTween = NULL;
	if (bIsSerial == true)
	{
		pLineTween = (CLineTweenRotation*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_ROTATE_TO);
	}
	else
	{
		pLineTween = (CLineTweenRotation*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_ROTATE_TO);
	}
	pLineTween->Init(glm::vec3(fFromX, fFromY, fFromZ), glm::vec3(fToX, fToY, fToZ), fTime);

	return 0;
}

n32 AddLineTweenCurve(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);

	f32 fP1x = lua_tonumber(a_pL, 2);
	f32 fP1Y = lua_tonumber(a_pL, 3);
	f32 fP1Z = lua_tonumber(a_pL, 4);

	f32 fP2X = lua_tonumber(a_pL, 5);
	f32 fP2Y = lua_tonumber(a_pL, 6);
	f32 fP2Z = lua_tonumber(a_pL, 7);

	f32 fP3X = lua_tonumber(a_pL, 8);
	f32 fP3Y = lua_tonumber(a_pL, 9);
	f32 fP3Z = lua_tonumber(a_pL, 10);

	f32 fVelocity = lua_tonumber(a_pL, 11);
	f32 fTime = lua_tonumber(a_pL, 12);
	tbool bIsSerial = lua_toboolean(a_pL, 13);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	if (pActor == NULL)
	{
		return 0;
	}

	CLineTweenCurve* pLineTween = NULL;
	if (bIsSerial == true)
	{
		pLineTween = (CLineTweenCurve*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_CURVE);
	}
	else
	{
		pLineTween = (CLineTweenCurve*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_CURVE);
	}
	pLineTween->Init(glm::vec3(fP1x, fP1Y, fP1Z), glm::vec3(fP2X, fP2Y, fP2Z), glm::vec3(fP3X, fP3Y, fP3Z), fTime);

	return 0;
}

n32 AddLineTweenFollow(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);
	n32 TargetActorID = lua_tointeger(a_pL, 2);
	f32 fDis = lua_tonumber(a_pL, 3);
	f32 fVelocity = lua_tonumber(a_pL, 4);
	tbool bIsSerial = lua_toboolean(a_pL, 5);

	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	CActor* pTargetActor = CGame::GetSingleton().GetCurrentScene()->FindActor(TargetActorID);
	if (pActor == NULL || pTargetActor == NULL)
	{
		return 0;
	}
	CLineTweenFollow* pLineTween = NULL;
	if (bIsSerial == true)
	{
		pLineTween = (CLineTweenFollow*)pActor->CreateSerialLineTween(E_LINETWEEN_TYPE_FOLLOW);
	}
	else
	{
		pLineTween = (CLineTweenFollow*)pActor->CreateParallelLineTween(E_LINETWEEN_TYPE_FOLLOW);
	}
	pLineTween->Init(pTargetActor, fDis, fVelocity);

	return 0;
}

n32 AddControl(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);
	CActor* pActor = CGame::GetSingleton().GetCurrentScene()->FindActor(ActorID);
	if (pActor == NULL)
	{
		return 0;
	}
	CShipControl::GetSingleton().pActor = pActor;
	return 0;
}

n32 AddToLineTweenGroup(lua_State* a_pL)
{
	n32 ActorID = lua_tointeger(a_pL, 1);
	CGame::GetSingleton().GetCurrentScene()->AddToLineTweenGroup(ActorID);
	return 0;
}

n32 LineTweenGroupFollow(lua_State* a_pL)
{
	n32 TargetActorID = lua_tointeger(a_pL, 1);
	f32 fDis = lua_tonumber(a_pL, 2);
	f32 fVelocity = lua_tonumber(a_pL, 3);

	CGame::GetSingleton().GetCurrentScene()->LineTweenGroupFollow(TargetActorID, fDis, fVelocity);
	return 0;
}
