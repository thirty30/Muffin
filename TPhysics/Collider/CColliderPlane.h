#pragma once
#include "TPhysicsInclude.h"
#include "CColliderBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CColliderPlane : public CColliderBase
	{
	public:
		glm::vec3 m_vDirection;
		f32 m_fConstant;

	public:
		CColliderPlane();
		~CColliderPlane();

		virtual void SetScale(glm::vec3 a_vScale) override {}
	};
}
