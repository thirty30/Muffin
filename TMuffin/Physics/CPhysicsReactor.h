#pragma once
#include "TMuffinSysInclude.h"

class SCollisionCallBackInfo;
class CPhysicsComponent;
class CPhysicsReactor
{
private:
	hash_map<u64, CPhysicsComponent*> m_mapID2PhysicsObj;
	vector<SCollisionCallBackInfo*> m_vecCallBackArray;

public:
	CPhysicsReactor();
	~CPhysicsReactor();

	void AddObject(CPhysicsComponent* a_pObject);
	void RemoveObject(CPhysicsComponent* a_pObject);
	CPhysicsComponent* FindObject(u64 a_nGUID);

	void RefreshColliderPosition();
	void PhysicsLoop();
	void CalcRigidBodyMotion();
	void CalcCollision();
	void CollisionCallBack();
};
