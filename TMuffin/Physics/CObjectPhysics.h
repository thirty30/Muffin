#pragma once

struct SCollisionCallBackInfo
{
	CGameObject* m_pSrc;
	CGameObject* m_pTar;
};

class CObjectPhysics
{
private:
	glm::vec3 m_vGravity;
	vector<SCollisionCallBackInfo*> m_vecCallBackArray;

public:
	CObjectPhysics();
	~CObjectPhysics();

	void PhysicsObjects();
	void CalcRigidBodyMotion();
	void CalcCollision();
};
