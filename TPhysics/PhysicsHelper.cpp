#include "PhysicsHelper.h"
#include "Body/CRigidBody.h"
#include "Body/CSoftBody.h"
#include "CPhysicsObject.h"
#include "Collider/CColliderBase.h"
#include "Collider/CColliderBase.h"
#include "Collider/CColliderBox.h"
#include "Collider/CColliderPlane.h"
#include "Collider/CColliderSphere.h"
#include "Collider/CColliderCloth.h"


void CalcColliderIsHit(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo)
{
	EColliderType eSrcType = a_pSrcObj->GetColliderType();
	EColliderType eTarType = a_pTarObj->GetColliderType();
	if (eSrcType == E_NULL_COLLIDER || eTarType == E_NULL_COLLIDER)
	{
		return;
	}

	switch (eSrcType)
	{
	case E_PLANE_COLLIDER:
	{
		if (eTarType == E_SPHERE_COLLIDER)
		{
			doSphere2Plane(a_pTarObj, a_pSrcObj, a_rCollisionInfo);
		}
	}
	break;
	case E_SPHERE_COLLIDER:
	{
		if (eTarType == E_PLANE_COLLIDER)
		{
			doSphere2Plane(a_pSrcObj, a_pTarObj, a_rCollisionInfo);
		}
		else if (eTarType == E_SPHERE_COLLIDER)
		{
			doSphere2Sphere(a_pSrcObj, a_pTarObj, a_rCollisionInfo);
		}
		else if (eTarType == E_BOX_COLLIDER)
		{
			doSphere2Box(a_pSrcObj, a_pTarObj, a_rCollisionInfo);
		}
		else if (eTarType == E_CLOTH_COLLIDER)
		{
			doSphere2Cloth(a_pSrcObj, a_pTarObj, a_rCollisionInfo);
		}
	}
	break;
	case E_BOX_COLLIDER:
	{
		if (eTarType == E_SPHERE_COLLIDER)
		{
			doSphere2Box(a_pTarObj, a_pSrcObj, a_rCollisionInfo);
		}
	}
	break;
	case E_CLOTH_COLLIDER:
	{
		if (eTarType == E_SPHERE_COLLIDER)
		{
			doSphere2Cloth(a_pTarObj, a_pSrcObj, a_rCollisionInfo);
		}
	}
	break;
	default:
		break;
	}
}

void doSphere2Plane(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo)
{
	CColliderSphere* pSrcCollider = a_pSrcObj->GetCollider<CColliderSphere>();
	CColliderPlane* pTarCollider = a_pTarObj->GetCollider<CColliderPlane>();

	glm::vec3 vNormal = pTarCollider->m_vDirection;
	f32 fConstant = pTarCollider->m_fConstant;
	glm::vec3 vCenter = pSrcCollider->m_vCenter + a_pSrcObj->GetPosition();

	f32 t = (glm::dot(vNormal, vCenter) - fConstant) / glm::dot(vNormal, vNormal);
	a_rCollisionInfo.m_vHitPoint = vCenter - t * vNormal;

	f32 fHitDis = glm::distance(vCenter, a_rCollisionInfo.m_vHitPoint);
	if (fHitDis <= pSrcCollider->m_fRadius)
	{
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_fIntersectDis = pSrcCollider->m_fRadius - fHitDis;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(vCenter - a_rCollisionInfo.m_vHitPoint);

		if (pSrcCollider->m_bIsTrigger == true || pTarCollider->m_bIsTrigger == true)
		{
			return;
		}

		CRigidBody* pSrcRB = a_pSrcObj->GetBody<CRigidBody>();
		CRigidBody* pTarRB = a_pTarObj->GetBody<CRigidBody>();
		if (pSrcRB == NULL || pTarRB == NULL)
		{
			return;
		}
		vCenter = vCenter + a_rCollisionInfo.m_vHitNormal * a_rCollisionInfo.m_fIntersectDis;
		a_pSrcObj->SetPosition(vCenter - pSrcCollider->m_vCenter);
		pSrcRB->m_vVelocity = glm::reflect(pSrcRB->m_vVelocity, a_rCollisionInfo.m_vHitNormal);
		pSrcRB->m_vVelocity *= glm::min(1.0f, pSrcCollider->m_fElastic * pTarCollider->m_fElastic);
	}
}

void doSphere2Sphere(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo)
{
	CColliderSphere* pSrcCollider = a_pSrcObj->GetCollider<CColliderSphere>();
	CColliderSphere* pTarCollider = a_pTarObj->GetCollider<CColliderSphere>();
	CRigidBody* pSrcRB = a_pSrcObj->GetBody<CRigidBody>();
	CRigidBody* pTarRB = a_pTarObj->GetBody<CRigidBody>();
	glm::vec3 vCenter1 = pSrcCollider->m_vCenter + a_pSrcObj->GetPosition();
	glm::vec3 vCenter2 = pTarCollider->m_vCenter + a_pTarObj->GetPosition();

	f32 fHitDis = glm::distance(vCenter1, vCenter2);
	if (fHitDis <= pSrcCollider->m_fRadius + pTarCollider->m_fRadius)
	{
		f32 fDepth = pSrcCollider->m_fRadius + pTarCollider->m_fRadius - fHitDis;
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(vCenter1 - vCenter2);
		glm::vec3 vBackDir = -a_rCollisionInfo.m_vHitNormal;
		glm::vec3 vBackPoint = vCenter2 + vBackDir * (vCenter1 + pTarCollider->m_fRadius);
		a_rCollisionInfo.m_fIntersectDis = glm::distance(vCenter1, vBackPoint);
		a_rCollisionInfo.m_vHitPoint = vCenter2 + vBackDir * pTarCollider->m_fRadius;

		if (pSrcCollider->m_bIsTrigger == true || pTarCollider->m_bIsTrigger == true)
		{
			return;
		}

		if (pSrcRB == NULL || pTarRB == NULL)
		{
			return;
		}

		glm::vec3 vSrcV = pSrcRB->m_vVelocity;
		glm::vec3 vTarV = pTarRB->m_vVelocity;
		f32 fElastic = glm::min(1.0f, pSrcCollider->m_fElastic * pTarCollider->m_fElastic);

		//a_pSrcObj->SetPosition(pSrcCollider->GetCenter() + a_rCollisionInfo.m_vHitNormal * fDepth);
		pSrcRB->m_vVelocity = (fElastic * pTarRB->m_fMass * (vTarV - vSrcV) + pSrcRB->m_fMass * vSrcV + pTarRB->m_fMass * vTarV) / (pSrcRB->m_fMass + pTarRB->m_fMass);

		a_pTarObj->SetPosition(vCenter2 - (pTarCollider->m_vCenter + vBackDir * fDepth));
		pTarRB->m_vVelocity = (fElastic * pSrcRB->m_fMass * (vSrcV - vTarV) + pSrcRB->m_fMass * vSrcV + pTarRB->m_fMass * vTarV) / (pSrcRB->m_fMass + pTarRB->m_fMass);
	}
}

void doSphere2Box(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo)
{
	CColliderSphere* pSrcCollider = a_pSrcObj->GetCollider<CColliderSphere>();
	CColliderBox* pTarCollider = a_pTarObj->GetCollider<CColliderBox>();
	glm::vec3 vMin = pTarCollider->GetMinPoint() + a_pTarObj->GetPosition();
	glm::vec3 vMax = pTarCollider->GetMaxPoint() + a_pTarObj->GetPosition();
	glm::vec3 vCenter = pSrcCollider->m_vCenter + a_pSrcObj->GetPosition();
	for (n32 i = 0; i < 3; i++) {
		f32 v = vCenter[i];
		v = glm::max(v, vMin[i]);
		v = glm::min(v, vMax[i]);
		a_rCollisionInfo.m_vHitPoint[i] = v;
	}
	f32 fHitDis = glm::distance(vCenter, a_rCollisionInfo.m_vHitPoint);
	if (fHitDis <= pSrcCollider->m_fRadius)
	{
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_fIntersectDis = pSrcCollider->m_fRadius - fHitDis;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(vCenter - a_rCollisionInfo.m_vHitPoint);

		CRigidBody* pSrcRB = a_pSrcObj->GetBody<CRigidBody>();
		CRigidBody* pTarRB = a_pTarObj->GetBody<CRigidBody>();
		if (pSrcRB == NULL || pTarRB == NULL)
		{
			return;
		}
		vCenter = vCenter + a_rCollisionInfo.m_vHitNormal * a_rCollisionInfo.m_fIntersectDis;
		a_pSrcObj->SetPosition(vCenter - pSrcCollider->m_vCenter);
		pSrcRB->m_vVelocity = glm::reflect(pSrcRB->m_vVelocity, a_rCollisionInfo.m_vHitNormal);
		pSrcRB->m_vVelocity *= glm::min(1.0f, pSrcCollider->m_fElastic * pTarCollider->m_fElastic);
	}
}

void doSphere2Cloth(CPhysicsObject* a_pSrcObj, CPhysicsObject* a_pTarObj, SCollisionResult& a_rCollisionInfo)
{
	CColliderSphere* pSrcCollider = a_pSrcObj->GetCollider<CColliderSphere>();
	CColliderCloth* pTarCollider = a_pTarObj->GetCollider<CColliderCloth>();

	CRigidBody* pRB = a_pSrcObj->GetBody<CRigidBody>();
	CSoftBody* pSB = a_pTarObj->GetBody<CSoftBody>();

	glm::vec3 vCenter = pSrcCollider->m_vCenter + a_pSrcObj->GetPosition();
	//1. test sphere and AABB
	glm::vec3 vMin = pTarCollider->GetMinPoint();
	glm::vec3 vMax = pTarCollider->GetMaxPoint();
	glm::vec3 vHitPoint;
	for (n32 i = 0; i < 3; i++) {
		f32 v = vCenter[i];
		v = glm::max(v, vMin[i]);
		v = glm::min(v, vMax[i]);
		vHitPoint[i] = v;
	}
	f32 fHitDis = glm::distance(vCenter, vHitPoint);

	//2. test sphere and all nodes
	if (fHitDis <= pSrcCollider->m_fRadius)
	{
		n32 nIdx = pTarCollider->IntegrateNode(vCenter, pSrcCollider->m_fRadius);
		if (nIdx < 0)
		{
			return;
		}
		CSoftBodyNode* pNode = pSB->GetNode(nIdx);
		glm::vec3 vSrcV = pRB->m_vVelocity;
		glm::vec3 vTarV = pNode->m_vVelocity;

		pRB->m_vVelocity = (0.1f * pNode->m_fMass * (vTarV - vSrcV) + pRB->m_fMass * vSrcV + pNode->m_fMass * vTarV) / (pRB->m_fMass + pNode->m_fMass);
		pNode->m_vVelocity = (0.1f * pRB->m_fMass * (vSrcV - vTarV) + pRB->m_fMass * vSrcV + pNode->m_fMass * vTarV) / (pRB->m_fMass + pNode->m_fMass);
	}
	//a_rCollisionInfo.m_vHitPoint = vHitPoint;
	//a_rCollisionInfo.m_bIsHit = true;
	//a_rCollisionInfo.m_fIntersectDis = pSrcCollider->GetRadius() - fHitDis;
	//a_rCollisionInfo.m_vHitNormal = glm::normalize(pSrcCollider->GetCenter() - a_rCollisionInfo.m_vHitPoint);
}

void RK4(glm::vec3& a_vPosition, glm::vec3& a_vVelocity, glm::vec3& a_vAcc, f32 a_fDT)
{
	glm::vec3 v1, v2, v3, v4;

	v1 = a_vVelocity + a_vAcc * 0.0f;
	v2 = a_vVelocity + a_vAcc * a_fDT * 0.5f;
	v3 = a_vVelocity + a_vAcc * a_fDT * 0.5f;
	v4 = a_vVelocity + a_vAcc * a_fDT;

	glm::vec3 v = 1.0f / 6.0f * (v1 + 2.0f * (v2 + v3) + v4);
	a_vVelocity += 1.0f / 6.0f * (a_vAcc + 2.0f * (a_vAcc + a_vAcc) + a_vAcc) * a_fDT;
	a_vPosition += v * a_fDT;
}

