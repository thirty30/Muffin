#pragma once

class T_DLL_EXPORT CPhysicsObject
{
private:
	u64 m_nMuffinPhysicsObectGUID;
	CGameObject* m_pGameObject;
	CRigidBody* m_pRigidBody;
	CBaseCollider* m_pCollider;

	friend class CPhysicsReactor;

private:
	virtual void OnCollision(SCollisionInfo& a_rCollision) {}

public:
	CPhysicsObject(CGameObject* a_pGameObject);
	virtual ~CPhysicsObject();

	CRigidBody* CreateRigidBody();
	CBaseCollider* CreateCollider(EColliderType a_eType);

	void RefreshColliderPostion();
	
};
