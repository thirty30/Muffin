#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"

namespace TPhysics
{
	class T_DLL_EXPORT CBodyBase
	{
	private:
		EBodyType m_eType;

	public:
		CBodyBase(EBodyType a_eType) { this->m_eType = a_eType; }
		virtual ~CBodyBase() {}

		EBodyType GetType() { return this->m_eType; }
	};
}


