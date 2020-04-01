#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"
#include "CBodyBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CRigidBody : public CBodyBase
	{
	public:
		tbool m_bUseGravity;
		glm::vec3 m_vGravity;
		tbool m_bIsStatic; // If true it cannot move in physics frame

		f32 m_fMass;
		glm::vec3 m_vForce;
		glm::vec3 m_vVelocity;
		glm::vec3 m_vAccel;

	public:
		CRigidBody();
		~CRigidBody() {}
	};
}


