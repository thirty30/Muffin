#include "CRigidBody.h"

CRigidBody::CRigidBody() : CBodyBase(E_RIGID_BODY)
{
	this->m_bUseGravity = true;
	this->m_vGravity = GRAVITY_ACCELERATION;
	this->m_bIsStatic = false;

	this->m_fMass = 1.0f;
	this->m_vForce = glm::vec3(0, 0, 0);
	this->m_vVelocity = glm::vec3(0, 0, 0);
	this->m_vAccel = glm::vec3(0, 0, 0);
}
