#pragma once

class CRigidBody : public CComponent
{
public:
	tbool m_bUseGravity;
	f32 m_fMass;
	tbool m_bIsPassive; // If true it cannot move in physics frame

	glm::vec3 m_vVelocity;
	glm::vec3 m_vAccel;

public:
	CRigidBody()
	{
		this->m_eComponentType = E_COMPONENT_RIGIDBODY;
		this->m_bUseGravity = true;
		this->m_fMass = 0;
		this->m_bIsPassive = true;

		this->m_vVelocity = glm::vec3(0 ,0, 0);
		this->m_vAccel = glm::vec3(0, 0, 0);
	}
	~CRigidBody() {}
};

