#pragma once

struct SCollisionInfo
{
	tbool m_bIsHit;
	glm::vec3 m_vHitPoint;
	glm::vec3 m_vHitNormal;
	f32 m_fIntersectDis;

	SCollisionInfo()
	{
		this->m_bIsHit = false;
		this->m_fIntersectDis = 0;
	}
};

class CGameObject;
class CObjectPhysics : public CSingleton<CObjectPhysics>
{
private:
	glm::vec3 m_vGravity;
	f64 m_fLastFrameTime;

public:
	glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
	tbool TestSphereTriangle(CSphereCollider* a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint);

public:
	CObjectPhysics();
	~CObjectPhysics();

	tbool Init();

	void PhysicsObjects(f64 a_fCurFrameTime);
	void CalcRigidBodyMotion(f32 a_fDeltaTime);
	void CalcCollision();

	void CalcColliderIsHit(CBaseCollider* a_pCollider1, CBaseCollider* a_pCollider2, SCollisionInfo& a_rCollisionInfo);

	void doSphere2Plane(CSphereCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo);
	void doSphere2Sphere(CSphereCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo);
	void doSphere2Box(CSphereCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo);
	void doSphere2Mesh(CSphereCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, SCollisionInfo& a_rCollisionInfo);

	//void doPlane2Plane(CPlaneCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doPlane2Sphere(CPlaneCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doPlane2Box(CPlaneCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doPlane2Mesh(CPlaneCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);

	//void doBox2Plane(CBoxCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doBox2Sphere(CBoxCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doBox2Box(CBoxCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doBox2Mesh(CBoxCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);

	//void doMesh2Plane(CMeshCollider* a_pSrcCollider, CPlaneCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doMesh2Sphere(CMeshCollider* a_pSrcCollider, CSphereCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doMesh2Box(CMeshCollider* a_pSrcCollider, CBoxCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
	//void doMesh2Mesh(CMeshCollider* a_pSrcCollider, CMeshCollider* a_pTarCollider, glm::vec3& a_vClosestPoint);
};


