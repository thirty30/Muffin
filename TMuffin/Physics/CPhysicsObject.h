#pragma once

class T_DLL_EXPORT CPhysicsObject
{
private:
	u64 m_nMuffinPhysicsObectGUID;
	CGameObject* m_pGameObject;
	CRigidBody* m_pRigidBody;
	CColliderBase* m_pCollider;

	friend class CPhysicsReactor;

private:
	virtual void OnCollision(SCollisionInfo& a_rCollision) {}
	void RefreshColliderPostion();

public:
	CPhysicsObject(CGameObject* a_pGameObject);
	virtual ~CPhysicsObject();

	CRigidBody* CreateRigidBody();
	CColliderBase* CreateCollider(EColliderType a_eType);

	CRigidBody* GetRigidBody();
	CColliderBase* GetCollider(EColliderType a_eType);
};


