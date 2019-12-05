#include "pch.h"

CLineTweenScale::CLineTweenScale(u64 a_nID, CGameObject* a_pParent) : CLineTween(a_nID, a_pParent, E_LINETWEEN_TYPE_SCALE_TO)
{

}

CLineTweenScale::~CLineTweenScale()
{

}

void CLineTweenScale::Update()
{
	if (this->IsDone() == true)
	{
		return;
	}

	if (this->m_bIsEnable == false)
	{
		this->m_bIsEnable = true;
		this->m_pParentObject->m_vScale = this->m_vStartScale;
	}

	f32 fDeltaTime = TMuffin_GetDeltaFrameTime();
	this->m_fNowTime += fDeltaTime;

	this->m_pParentObject->m_vScale += this->m_vVelocity * fDeltaTime;

	if (this->m_fNowTime >= this->m_fTargetTime)
	{
		this->m_bIsDone = true;
		this->m_pParentObject->LineTweenDone(this->m_nLineTweenID);
	}
}

tbool CLineTweenScale::Init(glm::vec3 a_vStartScale, glm::vec3 a_vEndScale, f32 a_fTime)
{
	this->m_vStartScale = a_vStartScale;
	this->m_vEndScale = a_vEndScale;
	this->m_fTargetTime = a_fTime;

	glm::vec3 vDis = this->m_vEndScale - this->m_vStartScale;
	this->m_vVelocity = vDis / this->m_fTargetTime;
	return true;
}
