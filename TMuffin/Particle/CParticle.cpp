#include "pch.h"

CParticle::CParticle() : CGraphicsObject(this)
{
	this->m_vAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_fLifeTime = 0;
}

CParticle::~CParticle()
{

}
