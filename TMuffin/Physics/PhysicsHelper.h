#pragma once

struct SCollisionResult
{
	tbool m_bIsHit;
	glm::vec3 m_vHitPoint;
	glm::vec3 m_vHitNormal;
	f32 m_fIntersectDis;

	SCollisionResult()
	{
		this->m_bIsHit = false;
		this->m_vHitPoint = glm::vec3(0, 0, 0);
		this->m_vHitNormal = glm::vec3(0, 0, 0);
		this->m_fIntersectDis = 0;
	}
};

class CPhysicsObject;
struct SCollisionCallBackInfo
{
	CPhysicsObject* m_pSrc;
	CPhysicsObject* m_pTar;
	glm::vec3 m_vHitPoint;
};

struct SCollisionInfo
{
	CPhysicsObject* m_pTarget;
	glm::vec3 m_vHitPoint;
};

extern void CalcColliderIsHit(CBaseCollider* a_pCollider1, CBaseCollider* a_pCollider2, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Plane(CSphereCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Sphere(CSphereCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Box(CSphereCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Mesh(CSphereCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
extern tbool TestSphereTriangle(CSphereCollider* a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint);

