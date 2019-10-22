#pragma once

class CParticle : public CGameObject
{
public:
	glm::vec3 m_vAcceleration;
	glm::vec3 m_vVelocity;
	f32 m_fLifeTime;

public:
	CParticle();
	~CParticle();
};



