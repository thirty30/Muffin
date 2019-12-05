#pragma once

class T_DLL_EXPORT CLineTweenScale : public CLineTween
{
private:
	glm::vec3 m_vStartScale;
	glm::vec3 m_vEndScale;
	
	f32 m_fNowTime;
	f32 m_fTargetTime;
	glm::vec3 m_vVelocity;

public:
	CLineTweenScale(u64 a_nID, CGameObject* a_pParent);
	~CLineTweenScale();

	virtual void Update();
	tbool Init(glm::vec3 a_vStartScale, glm::vec3 a_vEndScale, f32 a_fTime);
};
