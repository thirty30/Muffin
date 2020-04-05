#include "CPhysicsComponent.h"
#include "Engine/Engine.h"
#include "GameObject/CGameObject.h"

CPhysicsComponent::CPhysicsComponent()
{

}

CPhysicsComponent::~CPhysicsComponent()
{
	MUFFIN.GetPhysicsWorld()->RemoveObject(&this->m_phyObj);
}

void CPhysicsComponent::Init()
{
	if (this->m_phyObj.GetBodyType() == E_NULL_BODY)
	{
		if (this->m_strBodyName == "RigidBody")
		{
			CRigidBody* pRB = this->m_phyObj.CreateBody<CRigidBody>();
			pRB->m_bIsStatic = this->m_bIsStatic;
			pRB->m_bUseGravity = this->m_bUseGravity;
		}
		if (this->m_strBodyName == "SoftBody")
		{
			this->m_phyObj.CreateBody<CSoftBody>();
		}
	}
	if (this->m_phyObj.GetColliderType() == E_NULL_COLLIDER)
	{
		if (this->m_strColliderName == "Plane")
		{
			CColliderPlane* pCollider = this->m_phyObj.CreateCollider<CColliderPlane>();
			pCollider->m_fConstant = this->m_fConstant;
			pCollider->m_vDirection = this->m_vDirection;
		}
		if (this->m_strColliderName == "Sphere")
		{
			CColliderSphere* pCollider = this->m_phyObj.CreateCollider<CColliderSphere>();
			pCollider->m_vCenter = this->m_vCenter;
			pCollider->m_fRadius = this->m_fRadius;
			pCollider->m_fElastic = this->m_fElastic;
			pCollider->m_bIsTrigger = this->m_bIsTrigger;
		}
		if (this->m_strColliderName == "Box")
		{
			CColliderBox* pCollider = this->m_phyObj.CreateCollider<CColliderBox>();
			pCollider->m_vCenter = this->m_vCenter;
			pCollider->m_vSize = this->m_vSize;
			pCollider->m_bIsTrigger = this->m_bIsTrigger;
			pCollider->m_fElastic = this->m_fElastic;
		}
	}
	this->m_phyObj.m_strTag = this->m_strTag;
	this->m_phyObj.m_pCustomData = this->GetGameObject();
	this->m_phyObj.SetPosition(this->GetGameObject()->GetTransform().m_vPosition);
	this->m_phyObj.SetOnCollisionCallBack(TMuffin_OnCollision);
	MUFFIN.GetPhysicsWorld()->AddObject(&this->m_phyObj);
}

void CPhysicsComponent::Update()
{
	this->GetGameObject()->GetTransform().m_vPosition = this->m_phyObj.GetPosition();
}

extern void TMuffin_OnCollision(const SCollisionInfo& a_rCollision)
{
	CGameObject* pGameObject = static_cast<CGameObject*>(a_rCollision.m_pSrc->m_pCustomData);
	pGameObject->CallBackCollision(a_rCollision);
}
