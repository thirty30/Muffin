#pragma once
#include "TPhysicsInclude.h"
#include "CColliderBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CColliderCloth : public CColliderBase
	{
	private:
		f32 m_fRadius;					//node radius
		vector<glm::vec3> m_vecNodes;	//node position

	public:
		CColliderCloth();
		~CColliderCloth();

		virtual void SetScale(glm::vec3 a_vScale) override {}

		void Init(SClothInfo& a_rInfo);
		n32 GetNodeNum();
		f32 GetNodeRadius();
		void SetPostion(n32 a_nIdx, glm::vec3 a_vPostion);
		n32 IntegrateNode(glm::vec3 a_vPostion, f32 a_fRadius);
		glm::vec3 GetMinPoint();
		glm::vec3 GetMaxPoint();
	};
}

