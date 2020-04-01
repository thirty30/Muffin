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
	this->m_phyObj.m_pCustomData = this->GetGameObject();
	this->m_phyObj.SetPosition(this->GetGameObject()->GetTransform().m_vPosition);
	MUFFIN.GetPhysicsWorld()->AddObject(&this->m_phyObj);
}

void CPhysicsComponent::Update()
{
	this->GetGameObject()->GetTransform().m_vPosition = this->m_phyObj.GetPosition();
}
