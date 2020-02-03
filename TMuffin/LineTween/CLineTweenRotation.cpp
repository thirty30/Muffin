#include "CLineTweenRotation.h"
#include "GameObject/CGameObject.h"
#include "Engine/ExportFunction.h"

CLineTweenRotation::CLineTweenRotation(u64 a_nID, CGameObject* a_pParent) : CLineTween(a_nID, a_pParent, E_LINETWEEN_TYPE_ROTATE_TO)
{

}

CLineTweenRotation::~CLineTweenRotation()
{

}

void CLineTweenRotation::Update()
{
	if (this->IsDone() == true)
	{
		return;
	}

	if (this->m_bIsEnable == false)
	{
		this->m_bIsEnable = true;
		this->m_pParentObject->SetRotation(m_qStartRotation);
	}

	f32 fDeltaTime = TMuffin_GetDeltaFrameTime();
	this->m_fNowTime += fDeltaTime;

	f32 fAmountOfRotationCompleted = this->m_fNowTime / this->m_fTargetTime;
	glm::quat qCurrentRotation = glm::slerp(this->m_qStartRotation, this->m_qEndRotation, fAmountOfRotationCompleted);
	this->m_pParentObject->SetRotation(qCurrentRotation);

	if (this->m_fNowTime >= this->m_fTargetTime)
	{
		this->m_bIsDone = true;
		this->m_pParentObject->LineTweenDone(this->m_nLineTweenID);
	}
}

tbool CLineTweenRotation::Init(glm::vec3 a_vStartRotation, glm::vec3 a_vEndRotation, f32 a_fTime)
{
	glm::vec3 vStartAngle;
	vStartAngle.x = glm::radians(a_vStartRotation.x);
	vStartAngle.y = glm::radians(a_vStartRotation.y);
	vStartAngle.z = glm::radians(a_vStartRotation.z);
	this->m_qStartRotation = glm::quat(vStartAngle);

	glm::vec3 vEndAngle;
	vEndAngle.x = glm::radians(a_vEndRotation.x);
	vEndAngle.y = glm::radians(a_vEndRotation.y);
	vEndAngle.z = glm::radians(a_vEndRotation.z);
	this->m_qEndRotation = glm::quat(vEndAngle);

	this->m_fTargetTime = a_fTime;

	glm::quat qInvStart = glm::inverse(this->m_qStartRotation);
	glm::quat qRoationChange = qInvStart * this->m_qEndRotation;
	this->m_vVelocity = qRoationChange / this->m_fTargetTime;
	return true;
}
