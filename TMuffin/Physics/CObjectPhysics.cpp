#include "pch.h"
T_IMPLEMENT_SINGLETON(CObjectPhysics)

CObjectPhysics::CObjectPhysics()
{
	this->m_gravity = 9.8f;
}

CObjectPhysics::~CObjectPhysics()
{

}

void CObjectPhysics::PhysicsObjects()
{
	for (int i = 0; i < CGameObjectManager::GetSingleton().m_vList.size(); i++)
	{

	}
}
