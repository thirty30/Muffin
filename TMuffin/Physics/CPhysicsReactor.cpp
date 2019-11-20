#include "pch.h"

CPhysicsReactor::CPhysicsReactor()
{
	this->m_mapID2PhysicsObj.clear();
	this->m_vecCallBackArray.clear();
}

CPhysicsReactor::~CPhysicsReactor()
{
	this->m_mapID2PhysicsObj.clear();
	this->m_vecCallBackArray.clear();
}

void CPhysicsReactor::AddObject(CPhysicsObject* a_pObject)
{
	this->m_mapID2PhysicsObj[a_pObject->m_nMuffinPhysicsObectGUID] = a_pObject;
}

void CPhysicsReactor::RemoveObject(CPhysicsObject* a_pObject)
{
	u64 nGUID = a_pObject->m_nMuffinPhysicsObectGUID;
	if (this->FindObject(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2PhysicsObj.erase(nGUID);
}

CPhysicsObject* CPhysicsReactor::FindObject(u64 a_nGUID)
{
	hash_map<u64, CPhysicsObject*>::const_iterator iter = this->m_mapID2PhysicsObj.find(a_nGUID);
	if (iter == this->m_mapID2PhysicsObj.end())
	{
		return NULL;
	}
	return iter->second;
}

void CPhysicsReactor::RefreshColliderPosition()
{
	hash_map<u64, CPhysicsObject*>::const_iterator iter = this->m_mapID2PhysicsObj.begin();
	for (; iter != this->m_mapID2PhysicsObj.end(); iter++)
	{
		CPhysicsObject* pObj = iter->second;
		CGameObject* pGameObj = pObj->m_pGameObject;
		if (pGameObj->IsEnable() == true && pObj != NULL)
		{
			pObj->RefreshColliderPostion();
		}
	}
}


void CPhysicsReactor::PhysicsLoop()
{
	//1. refresh new collider center
	this->RefreshColliderPosition();

	//2. calc rigidbody motion and refresh collider center
	this->CalcRigidBodyMotion();
	this->RefreshColliderPosition();

	//3. calc collision
	this->CalcCollision();

	//4. callback
	this->CollisionCallBack();
}

void CPhysicsReactor::CalcRigidBodyMotion()
{
	f32 fDeltaTime = MUFFIN.GetDeltaFrameTime();
	hash_map<u64, CPhysicsObject*>::iterator iter = this->m_mapID2PhysicsObj.begin();
	for (; iter != this->m_mapID2PhysicsObj.end(); iter++)
	{
		CPhysicsObject* pPhysicsObj = iter->second;
		CGameObject* pGameObj = pPhysicsObj->m_pGameObject;
		if (pGameObj->IsEnable() == false)
		{
			continue;
		}
		CRigidBody* pRigidBody = pPhysicsObj->m_pRigidBody;
		if (pRigidBody == NULL || pRigidBody->m_bIsPassive == true)
		{
			continue;
		}
		pRigidBody->m_vAccel = pRigidBody->m_vForce / pRigidBody->m_fMass;
		glm::vec3 vNewAccel = pRigidBody->m_bUseGravity == true ? (pRigidBody->m_vGravity + pRigidBody->m_vAccel) : pRigidBody->m_vAccel;
		// S = vt + (1/2)at2
		glm::vec3 vDis = pRigidBody->m_vVelocity * fDeltaTime + 0.5f * vNewAccel * fDeltaTime * fDeltaTime;
		pRigidBody->m_vVelocity += vNewAccel * fDeltaTime;
		pPhysicsObj->m_pGameObject->m_vPosition += vDis;
	}
}

void CPhysicsReactor::CalcCollision()
{
	hash_map<u64, CPhysicsObject*>::iterator iterSrc = this->m_mapID2PhysicsObj.begin();
	for (; iterSrc != this->m_mapID2PhysicsObj.end(); iterSrc++)
	{
		CPhysicsObject* pSrcPhysicsObj = iterSrc->second;
		CGameObject* pSrcGameObj = pSrcPhysicsObj->m_pGameObject;
		if (pSrcGameObj->IsEnable() == false)
		{
			continue;
		}
		CColliderBase* pSrcBC = pSrcPhysicsObj->m_pCollider;
		if (pSrcBC == NULL)
		{
			continue;;
		}
		CRigidBody* pSrcRB = pSrcPhysicsObj->m_pRigidBody;

		hash_map<u64, CPhysicsObject*>::iterator iterTar = this->m_mapID2PhysicsObj.begin();
		for (; iterTar != this->m_mapID2PhysicsObj.end(); iterTar++)
		{
			CPhysicsObject* pTarPhysicsObj = iterTar->second;
			CGameObject* pTarGameObj = pTarPhysicsObj->m_pGameObject;
			if (pTarGameObj->IsEnable() == false)
			{
				continue;
			}
			if (pSrcPhysicsObj == pTarPhysicsObj)
			{
				continue;
			}
			CColliderBase* pTarBC = pTarPhysicsObj->m_pCollider;
			if (pTarBC == NULL)
			{
				continue;
			}
			CRigidBody* pTarRB = pTarPhysicsObj->m_pRigidBody;

			SCollisionResult rCollisionInfo;
			CalcColliderIsHit(pSrcBC, pTarBC, rCollisionInfo);
			if (rCollisionInfo.m_bIsHit == false)
			{
				continue;
			}

			SCollisionCallBackInfo* pCallBack = new SCollisionCallBackInfo();
			pCallBack->m_pSrc = pSrcPhysicsObj;
			pCallBack->m_pTar = pTarPhysicsObj;
			pCallBack->m_vHitPoint = rCollisionInfo.m_vHitPoint;
			pCallBack->m_vHitNormal = rCollisionInfo.m_vHitNormal;
			pCallBack->m_fIntersectDis = rCollisionInfo.m_fIntersectDis;
			this->m_vecCallBackArray.push_back(pCallBack);

			if (pSrcBC->IsTrigger() == true || pTarBC->IsTrigger() == true)
			{
				continue;
			}

			if (pSrcRB == NULL || pTarRB == NULL)
			{
				continue;
			}

			pSrcBC->SetCenter(pSrcBC->GetCenter() + rCollisionInfo.m_vHitNormal * rCollisionInfo.m_fIntersectDis);
			pSrcPhysicsObj->m_pGameObject->m_vPosition = pSrcBC->GetCenter();
			pSrcRB->m_vVelocity = glm::reflect(pSrcRB->m_vVelocity, rCollisionInfo.m_vHitNormal);
			pSrcRB->m_vVelocity *= glm::min(1.0f, pSrcBC->GetElastic() * pTarBC->GetElastic());
			
			// temp code sanshi mark
			if (pTarBC->GetColliderType() == E_COLLIDER_TYPE_SPHERE)
			{
				
				pTarBC->SetCenter(pTarBC->GetCenter() + (-rCollisionInfo.m_vHitNormal) * 0.01f);
				pTarPhysicsObj->m_pGameObject->m_vPosition = pTarBC->GetCenter();
				pTarRB->m_vVelocity = glm::reflect(pTarRB->m_vVelocity, -rCollisionInfo.m_vHitNormal);
				pTarRB->m_vVelocity *= glm::min(1.0f, pSrcBC->GetElastic() * pTarBC->GetElastic());
			}
		}
	}
}

void CPhysicsReactor::CollisionCallBack()
{
	n32 nCount = this->m_vecCallBackArray.size();
	for (n32 i = 0; i < nCount; i++)
	{
		SCollisionCallBackInfo* pInfo = this->m_vecCallBackArray[i];
		SCollisionInfo rParm1;
		rParm1.m_pTarget = pInfo->m_pTar;
		rParm1.m_vHitPoint = pInfo->m_vHitPoint;
		rParm1.m_vHitNormal = pInfo->m_vHitNormal;
		rParm1.m_fIntersectDis = pInfo->m_fIntersectDis;
		pInfo->m_pSrc->OnCollision(rParm1);

		SCollisionInfo rParm2;
		rParm2.m_pTarget = pInfo->m_pSrc;
		rParm2.m_vHitPoint = pInfo->m_vHitPoint;
		rParm2.m_vHitNormal = pInfo->m_vHitNormal;
		rParm2.m_fIntersectDis = pInfo->m_fIntersectDis;
		pInfo->m_pTar->OnCollision(rParm2);

		delete pInfo;
	}
	this->m_vecCallBackArray.clear();
}

