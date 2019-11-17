#include "pch.h"
#include "./CPhysicsObject.h"

CPhysicsObject::CPhysicsObject(CGameObject* a_pGameObject)
{
	this->m_nMuffinPhysicsObectGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_PHYSICS_OBJECT);
	this->m_pGameObject = a_pGameObject;
	this->m_pRigidBody = NULL;
	this->m_pCollider = NULL;

	MUFFIN.GetPhysicsReactor()->AddObject(this);
}

CPhysicsObject::~CPhysicsObject()
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

void CPhysicsObject::RefreshColliderPostion()
{
	if (this->m_pCollider == NULL)
	{
		return;
	}
	this->m_pCollider->SetCenter(this->m_pGameObject->m_vPosition);
}

CRigidBody* CPhysicsObject::CreateRigidBody()
{
	if (this->m_pRigidBody != NULL)
	{
		return this->m_pRigidBody;
	}
	this->m_pRigidBody = new CRigidBody();
	return this->m_pRigidBody;
}

CColliderBase* CPhysicsObject::CreateCollider(EColliderType a_eType)
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

CRigidBody* CPhysicsObject::GetRigidBody()
{
	return this->m_pRigidBody;
}

CColliderBase* CPhysicsObject::GetCollider(EColliderType a_eType)
{
	return this->m_pCollider;
}


