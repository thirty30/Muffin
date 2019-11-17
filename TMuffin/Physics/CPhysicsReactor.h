#pragma once

class CPhysicsReactor
{
private:
	hash_map<u64, CPhysicsObject*> m_mapID2PhysicsObj;
	vector<SCollisionCallBackInfo*> m_vecCallBackArray;

public:
	CPhysicsReactor();
	~CPhysicsReactor();

	void AddObject(CPhysicsObject* a_pObject);
	void RemoveObject(CPhysicsObject* a_pObject);
	CPhysicsObject* FindObject(u64 a_nGUID);

	void RefreshColliderPosition();
	void PhysicsLoop();
	void CalcRigidBodyMotion();
	void CalcCollision();
	void CollisionCallBack();
};
