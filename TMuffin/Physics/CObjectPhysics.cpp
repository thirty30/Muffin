#include "pch.h"
T_IMPLEMENT_SINGLETON(CObjectPhysics)

CObjectPhysics::CObjectPhysics()
{
	this->m_vGravity = glm::vec3(0, -9.8f, 0);
	this->m_fLastFrameTime = 0;
}

CObjectPhysics::~CObjectPhysics()
{

}

tbool CObjectPhysics::Init()
{
	return true;
}

glm::vec3 CObjectPhysics::ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	glm::vec3 n = glm::cross(b - a, c - a);
	float vc = glm::dot(n, glm::cross(a - p, b - p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = glm::dot(n, glm::cross(b - p, c - p));
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = glm::dot(n, glm::cross(c - p, a - p));
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}

tbool CObjectPhysics::TestSphereTriangle(CSphereCollider* a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint)
{
	// Find point P on triangle ABC closest to sphere center
	a_vClosestPoint = this->ClosestPtPointTriangle(a_rSphere->m_vCenter, a_vTriangleVectex1, a_vTriangleVectex2, ca_vTriangleVectex3);

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	glm::vec3 vDis = a_vClosestPoint - a_rSphere->m_vCenter;
	return glm::dot(vDis, vDis) <= a_rSphere->m_fRadius * a_rSphere->m_fRadius;
}

void CObjectPhysics::PhysicsObjects(f64 a_fCurFrameTime)
{
	f32 fDeltaTime = (f32)(a_fCurFrameTime - this->m_fLastFrameTime);
	//1. refresh new collider center
	CGameObjectManager::GetSingleton().RefreshColliderPosition();

	//2. calc rigidbody motion and refresh collider center
	this->CalcRigidBodyMotion(fDeltaTime);
	CGameObjectManager::GetSingleton().RefreshColliderPosition();

	//3. calc collision
	this->CalcCollision();
	this->m_fLastFrameTime = a_fCurFrameTime;
}

void CObjectPhysics::CalcRigidBodyMotion(f32 a_fDeltaTime)
{
	hash_map<n32, CGameObject*>::iterator iterSrc = CGameObjectManager::GetSingleton().m_mapID2GameObj.begin();
	for (; iterSrc != CGameObjectManager::GetSingleton().m_mapID2GameObj.end(); iterSrc++)
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
		glm::vec3 vDis = pSrcRB->m_vVelocity * a_fDeltaTime + 0.5f * vNewAccel * a_fDeltaTime * a_fDeltaTime;
		pSrcGameObj->m_vPosition += vDis;

		pSrcRB->m_vVelocity += vNewAccel * a_fDeltaTime;
	}
}

void CObjectPhysics::CalcCollision()
{
	hash_map<n32, CGameObject*>::iterator iterSrc = CGameObjectManager::GetSingleton().m_mapID2GameObj.begin();
	for (; iterSrc != CGameObjectManager::GetSingleton().m_mapID2GameObj.end(); iterSrc++)
	{
		CGameObject* pSrcGameObj = iterSrc->second;
		CBaseCollider* pSrcBC = pSrcGameObj->GetBaseCollider();
		if (pSrcBC == NULL)
		{
			continue;;
		}
		CRigidBody* pSrcRB = pSrcGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);

		hash_map<n32, CGameObject*>::iterator iterTar = CGameObjectManager::GetSingleton().m_mapID2GameObj.begin();
		for (; iterTar != CGameObjectManager::GetSingleton().m_mapID2GameObj.end(); iterTar++)
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
			this->CalcColliderIsHit(pSrcBC, pTarBC, rCollisionInfo);
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
			if (pTarBC->m_eColliderType == E_COLLIDER_TYPE_SPHERE)
			{
				CRigidBody* pTarRB = pTarGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
				pTarBC->m_vCenter += (-rCollisionInfo.m_vHitNormal) * 0.01f;
				pTarGameObj->m_vPosition = pTarBC->m_vCenter;
				pTarRB->m_vVelocity = glm::reflect(pTarRB->m_vVelocity, -rCollisionInfo.m_vHitNormal);
				pTarRB->m_vVelocity *= glm::min(1.0f, pSrcBC->m_fElastic * pTarBC->m_fElastic);
			}
			pSrcGameObj->OnCollision(pTarGameObj);
			pTarGameObj->OnCollision(pSrcGameObj);
		}
	}
}

void CObjectPhysics::CalcColliderIsHit(CBaseCollider* a_pCollider1, CBaseCollider* a_pCollider2, SCollisionInfo& a_rCollisionInfo)
{
	switch (a_pCollider1->m_eColliderType)
	{
	case E_COLLIDER_TYPE_PLANE:
	{
	}
	break;
	case E_COLLIDER_TYPE_SPHERE:
	{
		if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_PLANE)
		{
			this->doSphere2Plane((CSphereCollider*)a_pCollider1, (CPlaneCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_SPHERE)
		{
			this->doSphere2Sphere((CSphereCollider*)a_pCollider1, (CSphereCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_BOX)
		{
			this->doSphere2Box((CSphereCollider*)a_pCollider1, (CBoxCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_MESH)
		{
			this->doSphere2Mesh((CSphereCollider*)a_pCollider1, (CMeshCollider*)a_pCollider2, a_rCollisionInfo);
		}
	}
	break;
	case E_COLLIDER_TYPE_BOX:
	{
	}
	break;
	case E_COLLIDER_TYPE_MESH:
	{
	}
	break;
	default:
		break;
	}
}


void CObjectPhysics::doSphere2Plane(CSphereCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo)
{
	a_rCollisionInfo.m_vHitPoint = a_pSrcCollider->m_vCenter;
	if (a_pTarCollider->m_eAxis == E_PLANE_COLLIDER_AXIS_X)
	{
		a_rCollisionInfo.m_vHitPoint.x = a_pTarCollider->m_fPos;
	}
	else if (a_pTarCollider->m_eAxis == E_PLANE_COLLIDER_AXIS_Y)
	{
		a_rCollisionInfo.m_vHitPoint.y = a_pTarCollider->m_fPos;
	}
	else if (a_pTarCollider->m_eAxis == E_PLANE_COLLIDER_AXIS_Z)
	{
		a_rCollisionInfo.m_vHitPoint.z = a_pTarCollider->m_fPos;
	}
	f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
	if (fHitDis <= a_pSrcCollider->m_fRadius)
	{
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_fIntersectDis = a_pSrcCollider->m_fRadius - fHitDis;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(a_pSrcCollider->m_vCenter - a_rCollisionInfo.m_vHitPoint);
	}
}

void CObjectPhysics::doSphere2Sphere(CSphereCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo)
{
	f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_pTarCollider->m_vCenter);
	if (fHitDis < a_pSrcCollider->m_fRadius + a_pTarCollider->m_fRadius)
	{
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(a_pSrcCollider->m_vCenter - a_pTarCollider->m_vCenter);
		glm::vec3 vBackDir = glm::normalize(a_pSrcCollider->m_vCenter - a_pTarCollider->m_vCenter);
		glm::vec3 vBackPoint = a_pTarCollider->m_vCenter + vBackDir * (a_pSrcCollider->m_fRadius + a_pTarCollider->m_fRadius);
		a_rCollisionInfo.m_fIntersectDis = glm::distance(a_pSrcCollider->m_vCenter, vBackPoint);
		a_rCollisionInfo.m_vHitPoint = a_pTarCollider->m_vCenter + vBackDir * a_pTarCollider->m_fRadius;
	}
}

void CObjectPhysics::doSphere2Box(CSphereCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo)
{
	glm::vec3 vMin = a_pTarCollider->GetMinPoint();
	glm::vec3 vMax = a_pTarCollider->GetMaxPoint();
	for (int i = 0; i < 3; i++) {
		float v = a_pSrcCollider->m_vCenter[i];
		v = glm::max(v, vMin[i]);
		v = glm::min(v, vMax[i]);
		a_rCollisionInfo.m_vHitPoint[i] = v;
	}
	f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
	if (fHitDis <= a_pSrcCollider->m_fRadius)
	{
		a_rCollisionInfo.m_bIsHit = true;
		a_rCollisionInfo.m_fIntersectDis = a_pSrcCollider->m_fRadius - fHitDis;
		a_rCollisionInfo.m_vHitNormal = glm::normalize(a_pSrcCollider->m_vCenter - a_rCollisionInfo.m_vHitPoint);
	}
}

void CObjectPhysics::doSphere2Mesh(CSphereCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo)
{
	f32 fLastDis = FLT_MAX;
	for (n32 i = 0; i < a_pTarCollider->m_nTriangleCount; i += 3)
	{
		sMeshColliderTriangle* pTriangle = &a_pTarCollider->m_pTriangleoArray[i];
		tbool bCollided = this->TestSphereTriangle(a_pSrcCollider, pTriangle->m_vPoint1, pTriangle->m_vPoint2, pTriangle->m_vPoint3, a_rCollisionInfo.m_vHitPoint);
		if (bCollided == true)
		{
			a_rCollisionInfo.m_bIsHit = true;
			a_rCollisionInfo.m_vHitNormal = pTriangle->m_vTriangleNormal;
			f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
			a_rCollisionInfo.m_fIntersectDis = a_pSrcCollider->m_fRadius - fHitDis;
		}
	}
}

