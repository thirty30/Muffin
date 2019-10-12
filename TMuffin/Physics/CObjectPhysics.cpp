#include "pch.h"
T_IMPLEMENT_SINGLETON(CObjectPhysics)

CObjectPhysics::CObjectPhysics()
{
	this->m_vGravity = glm::vec3(0, -9.8f, 0);
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

tbool CObjectPhysics::TestSphereTriangle(CSphereCollider& a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint)
{
	// Find point P on triangle ABC closest to sphere center
	a_vClosestPoint = this->ClosestPtPointTriangle(a_rSphere.m_vCenter, a_vTriangleVectex1, a_vTriangleVectex2, ca_vTriangleVectex3);

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	glm::vec3 vDis = a_vClosestPoint - a_rSphere.m_vCenter;
	return glm::dot(vDis, vDis) <= a_rSphere.m_fRadius * a_rSphere.m_fRadius;
}

void CObjectPhysics::PhysicsObjects(f32 a_fDeltaTime)
{
	//1. calc new collider center
	CGameObjectManager::GetSingleton().RefreshColliderPosition();

	//2. calc rigidbody motion
	this->CalcRigidBodyMotion(a_fDeltaTime);
	
	//3. calc collision
	this->CalcCollision();
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
		glm::vec3 vDis = pSrcRB->m_vVelocity * a_fDeltaTime + 0.5f * vNewAccel * glm::pow(a_fDeltaTime, 2);
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
		//EColliderType eSrcType = pSrcGameObj->GetColliderType();

		hash_map<n32, CGameObject*>::iterator iterTar = CGameObjectManager::GetSingleton().m_mapID2GameObj.begin();
		for (; iterTar != CGameObjectManager::GetSingleton().m_mapID2GameObj.end(); iterTar++)
		{
			CGameObject* pTarGameObj = iterSrc->second;
			if (pSrcGameObj->m_nMuffinEngineGUID = pTarGameObj->m_nMuffinEngineGUID)
			{
				continue;
			}
			CBaseCollider* pTarBC = pTarGameObj->GetBaseCollider();
			if (pTarBC == NULL)
			{
				continue;
			}


			CRigidBody* pTarRB = pTarGameObj->GetComponent<CRigidBody>(E_COMPONENT_RIGIDBODY);
			//EColliderType eTarType = pTarGameObj->GetColliderType();
			//this->CalcCollider(pSrcBC, pTarBC);
		}

		//CSphereCollider* pCollider = pSrcGameObj->GetComponent<CSphereCollider>(E_COMPONENT_SPHERE_COLLIDER);
		//if (pCollider->m_vCenter.y - 1.0f <= 1.0f)
		//{
		//	pSrcRB->m_vVelocity = glm::reflect(pSrcRB->m_vVelocity, glm::vec3(0, 1, 0));
		//}

	}
}

void CObjectPhysics::CalcCollider(CGameObject* a_pObj1, CGameObject* a_pObj2)
{
	CBaseCollider* a_pC1 = a_pObj1->GetBaseCollider();
	switch (a_pC1->m_eColliderType)
	{
	case E_COLLIDER_TYPE_PLANE:
	{

	}
	break;
	case E_COLLIDER_TYPE_SPHERE:
	{
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

void CObjectPhysics::doSphereTriangle(CGameObject* a_pObj1, CGameObject* a_pObj2)
{
	/*
	f32 fLastDis = FLT_MAX;
	CMeshDrawInfo* pTargetDrawInfo = pTargetGameObj->m_pMeshRenderer.m_pMeshDrawInfo;
	for (n32 i = 0; i < pTargetDrawInfo->m_nTriangelIndexCount; i += 3)
	{
		n32 nVertex1 = pTargetDrawInfo->m_pTriangelIndices[i + 0];
		glm::vec3 vPoint1 = glm::vec3(pTargetDrawInfo->m_pVertices[nVertex1].X, pTargetDrawInfo->m_pVertices[nVertex1].Y, pTargetDrawInfo->m_pVertices[nVertex1].Z);

		n32 nVertex2 = pTargetDrawInfo->m_pTriangelIndices[i + 1];
		glm::vec3 vPoint2 = glm::vec3(pTargetDrawInfo->m_pVertices[nVertex2].X, pTargetDrawInfo->m_pVertices[nVertex2].Y, pTargetDrawInfo->m_pVertices[nVertex2].Z);

		n32 nVertex3 = pTargetDrawInfo->m_pTriangelIndices[i + 2];
		glm::vec3 vPoint3 = glm::vec3(pTargetDrawInfo->m_pVertices[nVertex3].X, pTargetDrawInfo->m_pVertices[nVertex3].Y, pTargetDrawInfo->m_pVertices[nVertex3].Z);

		glm::vec3 vPointClosest;// = this->ClosestPtPointTriangle(pCurGameObj->m_vPosition, vPoint1, vPoint2, vPoint3);

		Sphere sp;
		sp.c = pCurGameObj->m_vPosition;
		sp.r = 1;
		tbool bCollided = this->TestSphereTriangle(sp, vPoint1, vPoint2, vPoint3, vPointClosest);
		if (bCollided == true)
		{
			//printf("%f, %f, %f\n", pCurGameObj->m_vPosition.x, pCurGameObj->m_vPosition.y, pCurGameObj->m_vPosition.z);
			//f32 fDisTemp = 1.0f - glm::distance(pCurGameObj->m_vPositidon, vPointClosest);
			//pPhy->m_bIsPhysics = false;
			//glm::vec3 vInversepVelocity = -pPhy->m_vVelocity;
			//pCurGameObj->m_vPosition += vInversepVelocity * fDisTemp;
			//printf("======%f, %f, %f\n", pCurGameObj->m_vPosition.x, pCurGameObj->m_vPosition.y, pCurGameObj->m_vPosition.z);
			continue;
		}

		//debug sphere
		CGameObject* pDebugSphere = CGameObjectManager::GetSingleton().FindGameObjectByID(DEBUG_SPHERE_OBJECT_ID);
		f32 fDis = glm::distance(pCurGameObj->m_vPosition, vPointClosest);
		if (fDis < fLastDis)
		{
			fLastDis = fDis;
			pDebugSphere->m_vPosition = vPointClosest;
		}
	}
	*/
}