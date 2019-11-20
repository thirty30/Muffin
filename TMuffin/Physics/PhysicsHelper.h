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
	glm::vec3 m_vHitNormal;
	f32 m_fIntersectDis;
};

struct SCollisionInfo
{
	CPhysicsObject* m_pTarget;
	glm::vec3 m_vHitNormal;
	glm::vec3 m_vHitPoint;
	f32 m_fIntersectDis;
};

extern void CalcColliderIsHit(CColliderBase* a_pCollider1, CColliderBase* a_pCollider2, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Plane(CColliderSphere* a_pSrcCollider, CColliderPlane* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Sphere(CColliderSphere* a_pSrcCollider, CColliderSphere* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Box(CColliderSphere* a_pSrcCollider, CColliderBox* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern void doSphere2Mesh(CColliderSphere* a_pSrcCollider, CColliderMesh* a_pTarCollider, SCollisionResult& a_rCollisionInfo);
extern glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
extern tbool TestSphereTriangle(CColliderSphere* a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint);

