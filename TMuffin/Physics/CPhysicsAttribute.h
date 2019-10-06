#pragma once

class CPhysicsAttribute
{
public:
	EPhysicsType m_ePhysicsType;
	tbool m_bIsPhysics;
	f32 m_fInverseMass;

	glm::vec3 m_vVelocity;
	glm::vec3 m_vAccel;

public:
	CPhysicsAttribute()
	{
		this->m_ePhysicsType = E_PHYSICS_TYPE_INIT;
		this->m_bIsPhysics = false;
		this->m_fInverseMass = 0;

		this->m_vVelocity = glm::vec3(0 ,0, 0);
		this->m_vAccel = glm::vec3(0, 0, 0);
	}
};