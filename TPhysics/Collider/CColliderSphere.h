#pragma once
#include "TPhysicsInclude.h"
#include "CColliderBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CColliderSphere : public CColliderBase
	{
	public:
		f32 m_fRadius;

	public:
		CColliderSphere();
		~CColliderSphere();

		virtual void SetScale(glm::vec3 a_vScale) override;
	};
}

