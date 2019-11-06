#include "pch.h"

void CalcColliderIsHit(CBaseCollider* a_pCollider1, CBaseCollider* a_pCollider2, SCollisionResult& a_rCollisionInfo)
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
			doSphere2Plane((CSphereCollider*)a_pCollider1, (CPlaneCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_SPHERE)
		{
			doSphere2Sphere((CSphereCollider*)a_pCollider1, (CSphereCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_BOX)
		{
			doSphere2Box((CSphereCollider*)a_pCollider1, (CBoxCollider*)a_pCollider2, a_rCollisionInfo);
		}
		else if (a_pCollider2->m_eColliderType == E_COLLIDER_TYPE_MESH)
		{
			doSphere2Mesh((CSphereCollider*)a_pCollider1, (CMeshCollider*)a_pCollider2, a_rCollisionInfo);
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


void doSphere2Plane(CSphereCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo)
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

void doSphere2Sphere(CSphereCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo)
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

void doSphere2Box(CSphereCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo)
{
	glm::vec3 vMin = a_pTarCollider->GetMinPoint();
	glm::vec3 vMax = a_pTarCollider->GetMaxPoint();
	for (n32 i = 0; i < 3; i++) {
		f32 v = a_pSrcCollider->m_vCenter[i];
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

void doSphere2Mesh(CSphereCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo)
{
	glm::vec3 vMin = a_pTarCollider->m_vMinPoint;
	glm::vec3 vMax = a_pTarCollider->m_vMaxPoint;
	for (n32 i = 0; i < 3; i++) {
		f32 v = a_pSrcCollider->m_vCenter[i];
		v = glm::max(v, vMin[i]);
		v = glm::min(v, vMax[i]);
		a_rCollisionInfo.m_vHitPoint[i] = v;
	}
	f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
	if (fHitDis > a_pSrcCollider->m_fRadius)
	{
		return;
	}

	glm::vec3 vPoint = a_rCollisionInfo.m_vHitPoint;
	if (a_pSrcCollider->m_vCenter.x < a_pTarCollider->m_vMaxPoint.x && a_pSrcCollider->m_vCenter.x > a_pTarCollider->m_vMinPoint.x)
	{
		if (a_pSrcCollider->m_vCenter.y < a_pTarCollider->m_vMaxPoint.y && a_pSrcCollider->m_vCenter.y > a_pTarCollider->m_vMinPoint.y)
		{
			if (a_pSrcCollider->m_vCenter.z < a_pTarCollider->m_vMaxPoint.z && a_pSrcCollider->m_vCenter.z > a_pTarCollider->m_vMinPoint.z)
			{
				vPoint = a_pSrcCollider->m_vCenter;
			}
		}
	}

	sMeshColliderBox* pMeshBox = a_pTarCollider->FindBoxByPosition(vPoint);
	if (pMeshBox == NULL)
	{
		return;
	}
	f32 fLastDis = FLT_MAX;
	for (n32 i = 0; i < pMeshBox->m_vecTriangleIdx.size(); i += 3)
	{
		n32 nIdx = pMeshBox->m_vecTriangleIdx[i];
		sMeshColliderTriangle* pTriangle = &a_pTarCollider->m_pTriangleoArray[nIdx];
		tbool bCollided = TestSphereTriangle(a_pSrcCollider, pTriangle->m_vPoint1, pTriangle->m_vPoint2, pTriangle->m_vPoint3, a_rCollisionInfo.m_vHitPoint);
		if (bCollided == true)
		{
			a_rCollisionInfo.m_bIsHit = true;
			a_rCollisionInfo.m_vHitNormal = pTriangle->m_vTriangleNormal;
			f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
			a_rCollisionInfo.m_fIntersectDis = a_pSrcCollider->m_fRadius - fHitDis;
			return;
		}
	}

	//f32 fLastDis = FLT_MAX;
	//for (n32 i = 0; i < a_pTarCollider->m_nTriangleCount; i += 3)
	//{
	//	sMeshColliderTriangle* pTriangle = &a_pTarCollider->m_pTriangleoArray[i];
	//	tbool bCollided = TestSphereTriangle(a_pSrcCollider, pTriangle->m_vPoint1, pTriangle->m_vPoint2, pTriangle->m_vPoint3, a_rCollisionInfo.m_vHitPoint);
	//	if (bCollided == true)
	//	{
	//		a_rCollisionInfo.m_bIsHit = true;
	//		a_rCollisionInfo.m_vHitNormal = pTriangle->m_vTriangleNormal;
	//		f32 fHitDis = glm::distance(a_pSrcCollider->m_vCenter, a_rCollisionInfo.m_vHitPoint);
	//		a_rCollisionInfo.m_fIntersectDis = a_pSrcCollider->m_fRadius - fHitDis;
	//		return;
	//	}
	//}
}

glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
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

tbool TestSphereTriangle(CSphereCollider* a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint)
{
	// Find point P on triangle ABC closest to sphere center
	a_vClosestPoint = ClosestPtPointTriangle(a_rSphere->m_vCenter, a_vTriangleVectex1, a_vTriangleVectex2, ca_vTriangleVectex3);

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	glm::vec3 vDis = a_vClosestPoint - a_rSphere->m_vCenter;
	return glm::dot(vDis, vDis) <= a_rSphere->m_fRadius * a_rSphere->m_fRadius;
}