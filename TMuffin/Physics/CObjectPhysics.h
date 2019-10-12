#pragma once

class CGameObject;
class CObjectPhysics : public CSingleton<CObjectPhysics>
{
private:
	glm::vec3 m_vGravity;

public:
	glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
	tbool TestSphereTriangle(CSphereCollider& a_rSphere, glm::vec3 a_vTriangleVectex1, glm::vec3 a_vTriangleVectex2, glm::vec3 ca_vTriangleVectex3, glm::vec3& a_vClosestPoint);

public:
	CObjectPhysics();
	~CObjectPhysics();

	tbool Init();

	void PhysicsObjects(f32 a_fDeltaTime);
	void CalcRigidBodyMotion(f32 a_fDeltaTime);
	void CalcCollision();

	void CalcCollider(CGameObject* a_pObj1, CGameObject* a_pObj2);
	void doSphereTriangle(CGameObject* a_pObj1, CGameObject* a_pObj2);
};


