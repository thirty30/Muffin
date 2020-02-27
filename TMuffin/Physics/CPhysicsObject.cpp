#include "CPhysicsObject.h"
#include "CRigidBody.h"
#include "GameObject/CGameObject.h"
#include "Engine/Engine.h"
#include "Utility/CGUIDMaker.h"
#include "Physics/CColliderBase.h"
#include "CPhysicsReactor.h"
#include "CColliderBase.h"
#include "CColliderBox.h"
#include "CColliderCapsule.h"
#include "CColliderMesh.h"
#include "CColliderPlane.h"
#include "CColliderSphere.h"

CPhysicsComponent::CPhysicsComponent()
{
	this->m_pRigidBody = NULL;
	this->m_pCollider = NULL;
}

CPhysicsComponent::~CPhysicsComponent()
{
	if (this->m_pRigidBody != NULL)
	{
		delete this->m_pRigidBody;
	}
	if (this->m_pCollider != NULL)
	{
		delete this->m_pCollider;
	}
}

void CPhysicsComponent::RefreshColliderPostion()
{
	if (this->m_pCollider == NULL)
	{
		return;
	}
	this->m_pCollider->SetCenter(this->GetGameObject()->GetTransform().m_vPosition);
}

void CPhysicsComponent::Init()
{
	MUFFIN.GetPhysicsReactor()->AddObject(this);
}

CRigidBody* CPhysicsComponent::CreateRigidBody()
{
	if (this->m_pRigidBody != NULL)
	{
		return this->m_pRigidBody;
	}
	this->m_pRigidBody = new CRigidBody();
	return this->m_pRigidBody;
}

CColliderBase* CPhysicsComponent::CreateCollider(EColliderType a_eType)
{
	if (this->m_pCollider != NULL)
	{
		return this->m_pCollider;
	}
	switch (a_eType)
	{
	case E_COLLIDER_TYPE_PLANE:
	{
		this->m_pCollider = new CColliderPlane();
	}
	break;
	case E_COLLIDER_TYPE_SPHERE:
	{
		this->m_pCollider = new CColliderSphere();
	}
	break;
	case E_COLLIDER_TYPE_BOX:
	{
		this->m_pCollider = new CColliderBox();
	}
	break;
	case E_COLLIDER_TYPE_CAPSULE:
	{
		this->m_pCollider = new CColliderCapsule();
	}
	break;
	case E_COLLIDER_TYPE_MESH:
	{
		this->m_pCollider = new CColliderMesh();
	}
	break;
	default:
		break;
	}
	return this->m_pCollider;
}

CRigidBody* CPhysicsComponent::GetRigidBody()
{
	return this->m_pRigidBody;
}

CColliderBase* CPhysicsComponent::GetCollider(EColliderType a_eType)
{
	return this->m_pCollider;
}


