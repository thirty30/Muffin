#pragma once

class CPhysicsAttribute
{
public:
	EPhysicsType m_ePhysicsType;

	glm::vec3 m_vVelocity;
	glm::vec3 m_vAccel;
	f32 m_fInverseMass;
};