#include "CLineTweenMove.h"
#include "GameObject/CGameObject.h"
#include "Engine/ExportFunction.h"

CLineTweenMove::CLineTweenMove(u64 a_nID, CGameObject* a_pParent) : CLineTween(a_nID, a_pParent, E_LINETWEEN_TYPE_MOVE_TO)
{
	this->m_vVelocity = glm::vec3(0, 0, 0);
	this->m_fNowDis = 0;
	this->m_fEaseDis = 0;
	this->m_fTotalDis = 0;
}

CLineTweenMove::~CLineTweenMove()
{

}

void CLineTweenMove::Update()
{
	if (this->IsDone() == true)
	{
		return;
	}
	if (this->m_bIsEnable == false)
	{
		this->m_bIsEnable = true;
		this->m_pParentObject->m_vPosition = this->m_vStartPosition;
	}

	f32 fDeltaTime = TMuffin_GetDeltaFrameTime();
	this->m_fNowTime += fDeltaTime;

	f32 fNowDis = glm::distance(this->m_pParentObject->m_vPosition, this->m_vStartPosition);
	
	if (fNowDis < this->m_fEaseDis)
	{
		glm::vec3 vDis = this->m_vVelocity * fDeltaTime + 0.5f * this->m_vAcc * fDeltaTime * fDeltaTime;
		this->m_vVelocity += this->m_vAcc * fDeltaTime;
		this->m_pParentObject->m_vPosition += vDis;
	}
	else if (fNowDis < this->m_fTotalDis - this->m_fEaseDis)
	{
		this->m_pParentObject->m_vPosition += this->m_vMidVeloctiy * fDeltaTime;
	}
	else
	{
		glm::vec3 vDis = this->m_vVelocity * fDeltaTime + 0.5f * (-this->m_vAcc) * fDeltaTime * fDeltaTime;
		this->m_vVelocity += (-this->m_vAcc) * fDeltaTime;
		this->m_pParentObject->m_vPosition += vDis;
	}
	
	if (fNowDis >= this->m_fTotalDis)
	{
		this->m_bIsDone = true;
		this->m_pParentObject->LineTweenDone(this->m_nLineTweenID);
	}
}

tbool CLineTweenMove::Init(glm::vec3 a_vStartPosition, glm::vec3 a_vEndPosition, f32 a_fVelocity, f32 a_fEaseTime)
{
	this->m_vStartPosition = a_vStartPosition;
	this->m_vEndPosition = a_vEndPosition;
	
	glm::vec3 vDirction = glm::normalize(a_vEndPosition - a_vStartPosition);
	this->m_fTotalDis = glm::distance(a_vStartPosition, a_vEndPosition);
	this->m_vMidVeloctiy = a_fVelocity * vDirction;
	this->m_fEaseTime = a_fEaseTime;
	this->m_fEaseDis = this->m_fTotalDis / 6;
	this->m_vAcc = (this->m_fEaseDis * 2 / (a_fEaseTime * a_fEaseTime)) * vDirction;

	return true;
}
