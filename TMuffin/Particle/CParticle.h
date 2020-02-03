#pragma once
#include "TMuffinSysInclude.h"
#include "GameObject/CGameObject.h"
#include "Graphics/CGraphicsObject.h"

class CParticle : public CGameObject, public CGraphicsObject
{
public:
	glm::vec3 m_vAcceleration;
	glm::vec3 m_vVelocity;
	f32 m_fLifeTime;

public:
	CParticle();
	~CParticle();
};




