#pragma once

class CMotion : public CComponentBase
{
public:
	glm::vec3 m_vVelocity;

	T_SCS
		T_SCP(m_vVelocity, glm::vec3)
	T_SCE

public:
	CMotion();
	~CMotion();

	virtual void Update() override;
};
