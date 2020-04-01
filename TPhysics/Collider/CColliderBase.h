#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"

namespace TPhysics
{
	class T_DLL_EXPORT CColliderBase
	{
	private:
		EColliderType m_eColliderType;

	public:
		glm::vec3 m_vCenter;
		tbool m_bIsTrigger;
		f32 m_fElastic;
		

	public:
		CColliderBase(EColliderType a_eColliderType);
		virtual ~CColliderBase();

		T_INLINE EColliderType GetType() { return this->m_eColliderType; }

		// pure virtal function
		virtual void SetScale(glm::vec3 a_vScale) T_PURE;
	};
}



