#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"

namespace TPhysics
{
	class CPhysicsObject;
	class SCollisionCallBackInfo;
	class T_DLL_EXPORT CPhysicsWorld
	{
	private:
		hash_map<u64, CPhysicsObject*> m_mapID2PhysicsObj;
		vector<SCollisionCallBackInfo*> m_vecCallBackArray;
		u64 m_nGUIDGen;

	public:
		CPhysicsWorld();
		~CPhysicsWorld();

		void AddObject(CPhysicsObject* a_pObject);
		void RemoveObject(CPhysicsObject* a_pObject);
		CPhysicsObject* FindObject(u64 a_nGUID);

		void RefreshColliderPosition();
		void PhysicsLoop(f32 a_fDeltaTime);
		void CalcRigidBodyMotion(f32 a_fDeltaTime);
		void CalcCollision();
		void CollisionCallBack();
	};
}

