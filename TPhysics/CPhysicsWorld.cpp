#include "CPhysicsWorld.h"
#include "PhysicsHelper.h"
#include "Body/CRigidBody.h"
#include "Body/CSoftBody.h"
#include "CPhysicsObject.h"

CPhysicsWorld::CPhysicsWorld()
{
	this->m_mapID2PhysicsObj.clear();
	this->m_vecCallBackArray.clear();
	this->m_nGUIDGen = 0;
}

CPhysicsWorld::~CPhysicsWorld()
{
	this->m_mapID2PhysicsObj.clear();
	this->m_vecCallBackArray.clear();
}

void CPhysicsWorld::AddObject(CPhysicsObject* a_pObject)
{
	if (a_pObject->m_nGUID != 0)
	{
		return;
	}
	a_pObject->m_nGUID = ++this->m_nGUIDGen;
	this->m_mapID2PhysicsObj[a_pObject->m_nGUID] = a_pObject;
}

void CPhysicsWorld::RemoveObject(CPhysicsObject* a_pObject)
{
	u64 nGUID = a_pObject->GetGUID();
	CPhysicsObject* pObj = this->FindObject(nGUID);
	if (pObj == NULL)
	{
		return;
	}
	this->m_mapID2PhysicsObj.erase(nGUID);
}

CPhysicsObject* CPhysicsWorld::FindObject(u64 a_nGUID)
{
	hash_map<u64, CPhysicsObject*>::const_iterator iter = this->m_mapID2PhysicsObj.find(a_nGUID);
	if (iter == this->m_mapID2PhysicsObj.end())
	{
		return NULL;
	}
	return iter->second;
}

void CPhysicsWorld::RefreshColliderPosition()
{
	hash_map<u64, CPhysicsObject*>::const_iterator iter = this->m_mapID2PhysicsObj.begin();
	for (; iter != this->m_mapID2PhysicsObj.end(); iter++)
	{
		CPhysicsObject* pObj = iter->second;
		if (pObj != NULL)
		{
			pObj->RefreshColliderPostion();
		}
	}
}

void CPhysicsWorld::PhysicsLoop(f32 a_fDeltaTime)
{
	//1. refresh new collider center
	this->RefreshColliderPosition();

	//2. calc rigidbody motion and refresh collider center
	this->CalcRigidBodyMotion(a_fDeltaTime);
	this->RefreshColliderPosition();

	//3. calc collision
	this->CalcCollision();

	//4. callback
	this->CollisionCallBack();
}

void CPhysicsWorld::CalcRigidBodyMotion(f32 a_fDeltaTime)
{
	f32 fDeltaTime = a_fDeltaTime; // MUFFIN.GetDeltaFrameTime();
	hash_map<u64, CPhysicsObject*>::iterator iter = this->m_mapID2PhysicsObj.begin();
	for (; iter != this->m_mapID2PhysicsObj.end(); iter++)
	{
		CPhysicsObject* pPhysicsObj = iter->second;
		if (pPhysicsObj == NULL)
		{
			continue;
		}
		EBodyType eBodyType = pPhysicsObj->GetBodyType();
		
		if (eBodyType == E_NULL_BODY)
		{
			continue;
		}
		else if (eBodyType == E_RIGID_BODY)
		{
			CRigidBody* pRigidBody = pPhysicsObj->GetBody<CRigidBody>();
			if (pRigidBody->m_bIsStatic == true)
			{
				continue;
			}
			pRigidBody->m_vAccel = pRigidBody->m_vForce / pRigidBody->m_fMass;
			glm::vec3 vNewAccel = pRigidBody->m_bUseGravity == true ? (pRigidBody->m_vGravity + pRigidBody->m_vAccel) : pRigidBody->m_vAccel;
			RK4(pPhysicsObj->m_vNowPosition, pRigidBody->m_vVelocity, vNewAccel, fDeltaTime);

			//pRigidBody->m_vVelocity += vNewAccel * fDeltaTime;
			//glm::vec3 vDis = pRigidBody->m_vVelocity * fDeltaTime + 0.5f * vNewAccel * fDeltaTime * fDeltaTime;// S = vt + (1/2)at2
			//pPhysicsObj->m_vNowPosition += vDis;
		}
		else
		{
			CSoftBody* pSoftBody = pPhysicsObj->GetBody<CSoftBody>();
			pSoftBody->Update(fDeltaTime, GRAVITY_ACCELERATION);
		}
	}
}

void CPhysicsWorld::CalcCollision()
{
	hash_map<u64, CPhysicsObject*>::iterator iterSrc = this->m_mapID2PhysicsObj.begin();
	for (; iterSrc != this->m_mapID2PhysicsObj.end(); iterSrc++)
	{
		CPhysicsObject* pSrcPhysicsObj = iterSrc->second;
		if (pSrcPhysicsObj == NULL)
		{
			continue;
		}

		//hash_map<u64, CPhysicsObject*>::iterator iterTar = this->m_mapID2PhysicsObj.begin();
		hash_map<u64, CPhysicsObject*>::iterator iterTar = iterSrc;
		iterTar++;
		for (; iterTar != this->m_mapID2PhysicsObj.end(); iterTar++)
		{
			CPhysicsObject* pTarPhysicsObj = iterTar->second;
			if (pTarPhysicsObj == NULL)
			{
				continue;
			}

			SCollisionResult rCollisionInfo;
			CalcColliderIsHit(pSrcPhysicsObj, pTarPhysicsObj, rCollisionInfo);
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
		}
	}
}

void CPhysicsWorld::CollisionCallBack()
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
