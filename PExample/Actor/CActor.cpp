#include "stdafx.h"

CActor::CActor() : CPhysicsObject(this), CGraphicsObject(this)
{

}

CActor::~CActor()
{

}




CZone::CZone() : CPhysicsObject(this)
{

}

CZone::~CZone()
{

}

void CZone::OnCollision(SCollisionInfo& a_rCollision)
{
	this->SetEnable(false);
	lua_State* pL = CGame::GetSingleton().GetCurrentScene()->m_pLuaState;
	lua_getglobal(pL, "DistributeEvent");
	lua_pushnumber(pL, 5);
	lua_pcall(pL, 1, 0, 0);
}
