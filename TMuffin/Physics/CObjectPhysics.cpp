#include "pch.h"

CObjectPhysics::CObjectPhysics()
{
	this->m_vGravity = glm::vec3(0.0f, GRAVITY_ACCELERATION, 0.0f);
	this->m_vecCallBackArray.clear();
}

CObjectPhysics::~CObjectPhysics()
{
	this->m_vecCallBackArray.clear();
}

void CObjectPhysics::PhysicsObjects()
{
	//1. refresh new collider center
	MUFFIN.GetGameObjectMgr()->RefreshColliderPosition();

	//2. calc rigidbody motion and refresh collider center
	this->CalcRigidBodyMotion();
	MUFFIN.GetGameObjectMgr()->RefreshColliderPosition();

	//3. calc collision
	this->CalcCollision();

	//4. callback
	n32 nCount = this->m_vecCallBackArray.size();
	for (n32 i = 0; i < nCount; i++)
	{
		SCollisionCallBackInfo* pInfo = this->m_vecCallBackArray[i];
		pInfo->m_pSrc->OnCollision(pInfo->m_pTar);
		pInfo->m_pTar->OnCollision(pInfo->m_pSrc);
		delete pInfo;
	}
	this->m_vecCallBackArray.clear();
}

void CObjectPhysics::CalcRigidBodyMotion()
{
	f32 fDeltaTime = MUFFIN.GetDeltaFrameTime();
	hash_map<u64, CGameObject*>::iterator iterSrc = MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.begin();
	for (; iterSrc != MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.end(); iterSrc++)
	{
		CGameObject* pSrcGameObj = iterSrc->second;
		CRigidBody* pSrcRB = pSrcGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
		if (pSrcRB == NULL || pSrcRB->m_bIsPassive == true)
		{
			continue;
		}

		glm::vec3 vNewAccel;
		if (pSrcRB->m_bUseGravity == true)
		{
			vNewAccel = this->m_vGravity + pSrcRB->m_vAccel;
		}
		else
		{
			vNewAccel = pSrcRB->m_vAccel;
		}

		// S = vt + (1/2)at2
		glm::vec3 vDis = pSrcRB->m_vVelocity * fDeltaTime + 0.5f * vNewAccel * fDeltaTime * fDeltaTime;
		pSrcGameObj->m_vPosition += vDis;

		pSrcRB->m_vVelocity += vNewAccel * fDeltaTime;
	}
}

void CObjectPhysics::CalcCollision()
{
	hash_map<u64, CGameObject*>::iterator iterSrc = MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.begin();
	for (; iterSrc != MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.end(); iterSrc++)
	{
		CGameObject* pSrcGameObj = iterSrc->second;
		CBaseCollider* pSrcBC = pSrcGameObj->GetBaseCollider();
		if (pSrcBC == NULL)
		{
			continue;;
		}
		CRigidBody* pSrcRB = pSrcGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);

		hash_map<u64, CGameObject*>::iterator iterTar = MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.begin();
		for (; iterTar != MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.end(); iterTar++)
		{
			CGameObject* pTarGameObj = iterTar->second;
			if (pSrcGameObj->m_nMuffinEngineGUID == pTarGameObj->m_nMuffinEngineGUID)
			{
				continue;
			}
			CBaseCollider* pTarBC = pTarGameObj->GetBaseCollider();
			if (pTarBC == NULL)
			{
				continue;
			}
			glm::vec3 vHitPoint(0.0f, 0.0f, 0.0f);
			SCollisionInfo rCollisionInfo;
			CalcColliderIsHit(pSrcBC, pTarBC, rCollisionInfo);
			if (rCollisionInfo.m_bIsHit == false)
			{
				continue;
			}
			if (pSrcRB == NULL)
			{
				continue;
			}
			pSrcBC->m_vCenter += rCollisionInfo.m_vHitNormal * rCollisionInfo.m_fIntersectDis;
			pSrcGameObj->m_vPosition = pSrcBC->m_vCenter;
			pSrcRB->m_vVelocity = glm::reflect(pSrcRB->m_vVelocity, rCollisionInfo.m_vHitNormal);
			pSrcRB->m_vVelocity *= glm::min(1.0f, pSrcBC->m_fElastic * pTarBC->m_fElastic);
			
			// temp code sanshi mark
			if (pTarBC->m_eColliderType == E_COLLIDER_TYPE_SPHERE)
			{
				CRigidBody* pTarRB = pTarGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
				pTarBC->m_vCenter += (-rCollisionInfo.m_vHitNormal) * 0.01f;
				pTarGameObj->m_vPosition = pTarBC->m_vCenter;
				pTarRB->m_vVelocity = glm::reflect(pTarRB->m_vVelocity, -rCollisionInfo.m_vHitNormal);
				pTarRB->m_vVelocity *= glm::min(1.0f, pSrcBC->m_fElastic * pTarBC->m_fElastic);
			}

			SCollisionCallBackInfo* pCallBack = new SCollisionCallBackInfo();
			pCallBack->m_pSrc = pSrcGameObj;
			pCallBack->m_pTar = pTarGameObj;
			this->m_vecCallBackArray.push_back(pCallBack);
		}
	}
}

