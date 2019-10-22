#include "pch.h"

CParticle::CParticle()
{
	this->m_vAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_fLifeTime = 0;
}

CParticle::~CParticle()
{

}
