#pragma once
#include "TMuffinSysInclude.h"
#include "PhysicsDefine.h"
#include "PhysicsHelper.h"
#include "Component/CComponentBase.h"

class CGameObject;
class CRigidBody;
class CColliderBase;
class T_DLL_EXPORT CPhysicsComponent : public CComponentBase
{
private:
	CRigidBody* m_pRigidBody;
	CColliderBase* m_pCollider;

	friend class CPhysicsReactor;

private:
	virtual void OnCollision(SCollisionInfo& a_rCollision) {}
	void RefreshColliderPostion();

protected:
	virtual void Init() override;

public:
	CPhysicsComponent();
	virtual ~CPhysicsComponent();

	CRigidBody* CreateRigidBody();
	CColliderBase* CreateCollider(EColliderType a_eType);

	CRigidBody* GetRigidBody();
	CColliderBase* GetCollider(EColliderType a_eType);
};

