#pragma once

class T_DLL_EXPORT CLineTweenCurve : public CLineTween
{
private:
	glm::vec3 m_vCurvePoint1;
	glm::vec3 m_vCurvePoint2;
	glm::vec3 m_vCurvePoint3;
	n32 m_nBezierIndex;
	vector<glm::vec3> m_vecBezier;
	f32 m_fTotalCurveLength;
	f32 m_fEaseLength;
	f32 m_fNowLength;

	f32 m_fVelocity;
	f32 m_fMidVelocity;
	f32 m_fAcc;

	f32 m_fNowTime;
	f32 m_fTargetTime;
	f32 m_fEaseTime;

public:
	CLineTweenCurve(u64 a_nID, CGameObject* a_pParent);
	~CLineTweenCurve();

	virtual void Update();
	tbool Init(glm::vec3 a_vP1, glm::vec3 a_vP2, glm::vec3 a_vP3, f32 a_fTime);
	tbool Init(glm::vec3 a_vP1, glm::vec3 a_vP2, glm::vec3 a_vP3, f32 a_fVelocity, f32 a_fEaseTime);
};


