#include "CPhysicsObject.h"
#include "Body/CRigidBody.h"
#include "Body/CSoftBody.h"
#include "Collider/CColliderBase.h"
#include "Collider/CColliderBox.h"
#include "Collider/CColliderPlane.h"
#include "Collider/CColliderSphere.h"
#include "Collider/CColliderCloth.h"
#include "CPhysicsWorld.h"

CPhysicsObject::CPhysicsObject()
{
	this->m_nGUID = 0;
	this->m_pBody = NULL;
	this->m_pCollider = NULL;
	this->m_pCustomData = NULL;
}

CPhysicsObject::~CPhysicsObject()
{
	if (this->m_pBody != NULL)
	{
		delete this->m_pBody;
	}
	if (this->m_pCollider != NULL)
	{
		delete this->m_pCollider;
	}
	this->m_pCustomData = NULL;
}

void CPhysicsObject::RefreshColliderPostion()
{
	//if (this->m_pCollider == NULL)
	//{
	//	return;
	//}
	//this->m_pCollider->m_vCenter = this->m_vNowPosition;
	//if (this->m_pCollider->GetType() == E_CLOTH_COLLIDER)
	//{
	//	CSoftBody* pSB = (CSoftBody*)this->m_pBody;
	//	for (n32 i = 0; i < pSB->m_vecNodes.size(); i++)
	//	{
	//		((CColliderCloth*)this->m_pCollider)->SetPostion(i, pSB->m_vecNodes[i].m_vPosition);
	//	}
	//}
}

EBodyType CPhysicsObject::GetBodyType()
{
	if (this->m_pBody == NULL)
	{
		return E_NULL_BODY;
	}
	return this->m_pBody->GetType();
}

EColliderType TPhysics::CPhysicsObject::GetColliderType()
{
	if (this->m_pCollider == NULL)
	{
		return E_NULL_COLLIDER;
	}
	return this->m_pCollider->GetType();
}

