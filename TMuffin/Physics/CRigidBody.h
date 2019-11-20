#pragma once

class CRigidBody
{
public:
	tbool m_bUseGravity;
	glm::vec3 m_vGravity;
	f32 m_fMass;
	glm::vec3 m_vForce;
	tbool m_bIsPassive; // If true it cannot move in physics frame

	glm::vec3 m_vVelocity;
	glm::vec3 m_vAccel;

public:
	CRigidBody()
	{
		this->m_bUseGravity = true;
		this->m_vGravity = GRAVITY_ACCELERATION;
		this->m_fMass = 1.0f;
		this->m_vForce = glm::vec3(0, 0, 0);
		this->m_bIsPassive = true;

		this->m_vVelocity = glm::vec3(0 ,0, 0);
		this->m_vAccel = glm::vec3(0, 0, 0);
	}
	~CRigidBody() {}
};

