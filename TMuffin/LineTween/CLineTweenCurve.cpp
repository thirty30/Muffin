#include "pch.h"

CLineTweenCurve::CLineTweenCurve(u64 a_nID, CGameObject* a_pParent) : CLineTween(a_nID, a_pParent, E_LINETWEEN_TYPE_CURVE)
{
	this->m_nBezierIndex = 0;
	this->m_vecBezier.clear();
	this->m_fTotalCurveLength = 0;
	this->m_fVelocity = 0;
}

CLineTweenCurve::~CLineTweenCurve()
{

}

void CLineTweenCurve::Update()
{
	if (this->IsDone() == true)
	{
		return;
	}
	if (this->m_bIsEnable == false)
	{
		this->m_bIsEnable = true;
		this->m_pParentObject->m_vPosition = this->m_vCurvePoint1;
	}

	f32 fDeltaTime = TMuffin_GetDeltaFrameTime();
	this->m_fNowTime += fDeltaTime;

	glm::vec3 vTempTarget = this->m_vecBezier[this->m_nBezierIndex];
	glm::vec3 vDirction = glm::normalize(vTempTarget - this->m_pParentObject->m_vPosition);

	this->m_pParentObject->m_vPosition += this->m_fVelocity * vDirction * fDeltaTime;

	f32 fTime = (this->m_fTargetTime / 50 * this->m_nBezierIndex);
	if (this->m_fNowTime >= fTime)
	{
		this->m_nBezierIndex++;
	}

	if (this->m_nBezierIndex >= this->m_vecBezier.size())
	{
		this->m_bIsDone = true;
		this->m_pParentObject->LineTweenDone(this->m_nLineTweenID);
	}
}

tbool CLineTweenCurve::Init(glm::vec3 a_vP1, glm::vec3 a_vP2, glm::vec3 a_vP3, f32 a_fTime)
{
	this->m_vCurvePoint1 = a_vP1;
	this->m_vCurvePoint2 = a_vP2;
	this->m_vCurvePoint3 = a_vP3;
	this->m_fTargetTime = a_fTime;

	this->m_vecBezier = GenerateBezierCurve(a_vP1, a_vP2, a_vP3);
	for (n32 i = 0; i < this->m_vecBezier.size() - 1; i++)
	{
		glm::vec3 vP1 = this->m_vecBezier[i];
		glm::vec3 vP2 = this->m_vecBezier[i + 1];
		this->m_fTotalCurveLength += glm::distance(vP1, vP2);
	}
	this->m_fTotalCurveLength += glm::distance(this->m_vecBezier[0], this->m_pParentObject->m_vPosition);
	this->m_fTotalCurveLength += glm::distance(this->m_vecBezier[49], this->m_pParentObject->m_vPosition);

	this->m_fVelocity = this->m_fTotalCurveLength / this->m_fTargetTime;

	return true;
}
