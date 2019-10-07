#include "pch.h"
T_IMPLEMENT_SINGLETON(CObjectPhysics)

CObjectPhysics::CObjectPhysics()
{
	this->m_vGravity = glm::vec3(0, -9.8f, 0);
}

CObjectPhysics::~CObjectPhysics()
{

}

void CObjectPhysics::PhysicsObjects(f32 a_fDeltaTime)
{
	hash_map<n32, CGameObject*>::iterator iter = CGameObjectManager::GetSingleton().m_mapID2GameObj.begin();
	for (; iter != CGameObjectManager::GetSingleton().m_mapID2GameObj.end(); iter++)
	{
		CGameObject* pCurGameObj = iter->second;
		if (pCurGameObj->NeedPhysics() == false)
		{
			continue;
		}
		CPhysicsAttribute* pPhy = &pCurGameObj->m_pPhysicsAttribute;
		if (pPhy->m_fInverseMass == 0)
		{
			continue;
		}
		
		glm::vec3 vNewAccel = this->m_vGravity + pPhy->m_vAccel;
		f32 fDisX = pPhy->m_vVelocity.x * a_fDeltaTime + 0.5f * vNewAccel.x * a_fDeltaTime * a_fDeltaTime;
		f32 fDisY = pPhy->m_vVelocity.y * a_fDeltaTime + 0.5f * vNewAccel.y * a_fDeltaTime * a_fDeltaTime;
		f32 fDisZ = pPhy->m_vVelocity.z * a_fDeltaTime + 0.5f * vNewAccel.z * a_fDeltaTime * a_fDeltaTime;

		pPhy->m_vVelocity.x += vNewAccel.x * a_fDeltaTime;
		pPhy->m_vVelocity.y += vNewAccel.y * a_fDeltaTime;
		pPhy->m_vVelocity.z += vNewAccel.z * a_fDeltaTime;

		pCurGameObj->m_vPosition += glm::vec3(fDisX, fDisY, fDisZ);

		//if (pCurGameObj->m_vPosition.y <= 2.0f)
		//{
		//	pPhy->m_vVelocity = glm::reflect(pPhy->m_vVelocity, glm::vec3(0, 1, 0));
		//}
		//if (pCurGameObj->m_vPosition.x >= 15.0f)
		//{
		//	pPhy->m_vVelocity = glm::reflect(pPhy->m_vVelocity, glm::vec3(-1, 0, 0));
		//}
	}
}
