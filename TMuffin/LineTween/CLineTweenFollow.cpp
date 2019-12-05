#include "pch.h"

CLineTweenFollow::CLineTweenFollow(u64 a_nID, CGameObject* a_pParent) : CLineTween(a_nID, a_pParent, E_LINETWEEN_TYPE_FOLLOW)
{

}

CLineTweenFollow::~CLineTweenFollow()
{

}

void CLineTweenFollow::Update()
{
	if (this->IsDone() == true)
	{
		return;
	}

	f32 fDeltaTime = TMuffin_GetDeltaFrameTime();
	this->m_fNowTime += fDeltaTime;

	f32 fDis = glm::distance(this->m_pTargetObject->m_vPosition, this->m_pParentObject->m_vPosition);
	if (fDis <= this->m_fDistance)
	{
		this->m_pParentObject->LineTweenDone(this->m_nLineTweenID);
		return;
	}
	glm::vec3 vDirection = glm::normalize(this->m_pTargetObject->m_vPosition - this->m_pParentObject->m_vPosition);
	this->m_pParentObject->m_vPosition += this->m_fVelocity * vDirection * fDeltaTime;
}

tbool CLineTweenFollow::Init(CGameObject* a_pTarget, f32 a_fDistance, f32 a_fVelocity)
{
	this->m_pTargetObject = a_pTarget;
	this->m_fDistance = a_fDistance;
	this->m_fVelocity = a_fVelocity;

	return true;
}
