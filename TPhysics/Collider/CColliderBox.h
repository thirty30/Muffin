#pragma once
#include "TPhysicsInclude.h"
#include "CColliderBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CColliderBox : public CColliderBase
	{
	public:
		glm::vec3 m_vSize;

		CColliderBox();
		~CColliderBox();

		T_INLINE glm::vec3 GetMinPoint()
		{
			return glm::vec3(this->m_vCenter.x - this->m_vSize.x, this->m_vCenter.y - this->m_vSize.y, this->m_vCenter.z - this->m_vSize.z);
		}
		T_INLINE glm::vec3 GetMaxPoint()
		{
			return glm::vec3(this->m_vCenter.x + this->m_vSize.x, this->m_vCenter.y + this->m_vSize.y, this->m_vCenter.z + this->m_vSize.z);
		}
		T_INLINE void SetSize(glm::vec3 a_vSize)
		{
			this->m_vSize = a_vSize;
		}

		virtual void SetScale(glm::vec3 a_vScale) override
		{
			this->m_vSize *= a_vScale;
		}
	};
}

