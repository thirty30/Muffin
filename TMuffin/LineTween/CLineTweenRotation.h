#pragma once

class T_DLL_EXPORT CLineTweenRotation : public CLineTween
{
private:
	glm::quat m_qStartRotation;
	glm::quat m_qEndRotation;

	glm::quat m_qEaseRotation;

	f32 m_fNowTime;
	f32 m_fTargetTime;
	glm::quat m_vVelocity;

public:
	CLineTweenRotation(u64 a_nID, CGameObject* a_pParent);
	~CLineTweenRotation();

	virtual void Update();
	tbool Init(glm::vec3 a_vStartRotation, glm::vec3 a_vEndRotation, f32 a_fTime);
};
