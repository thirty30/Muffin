#pragma once
#include "TPhysicsInclude.h"
#include "PhysicsDefine.h"
#include "CBodyBase.h"

namespace TPhysics
{
	class T_DLL_EXPORT CSoftBodyNode
	{
	public:
		f32 m_fMass;
		f32 m_fRadius;
		glm::vec3 m_vPosition;
		glm::vec3 m_vVelocity;
		glm::vec3 m_vAcceleration;
		glm::vec3 m_vForce;
		vector<n32> m_vecNeighbor;

		CSoftBodyNode();
		~CSoftBodyNode();

		tbool IsFixed();
		tbool IsNeighbor(n32 a_nIdx);
	};

	class T_DLL_EXPORT CSoftBodySpring
	{
	public:
		CSoftBodyNode* m_pNodeA;
		CSoftBodyNode* m_pNodeB;
		f32 m_fSpringConstant;
		f32 m_fRestingLength;
		glm::vec3 m_vCurrentForceA2B;

		CSoftBodySpring();
		~CSoftBodySpring();

		void Init(CSoftBodyNode* a_pNodeA, CSoftBodyNode* a_pNodeB, f32 a_fConstant);
		void UpdateSpringForce();
		void ApplyForce();
		CSoftBodyNode* GetOther(CSoftBodyNode* a_pNode);
	};

	class T_DLL_EXPORT CSoftBody : public CBodyBase
	{
	public:
		vector<CSoftBodyNode> m_vecNodes;
		vector<CSoftBodySpring> m_vecSprings;

	public:
		CSoftBody();
		~CSoftBody();

		void Init(SClothInfo& a_rInfo);
		n32 GetNodeNum();
		f32 GetNodeRadius(n32 a_nIdx);
		glm::vec3 GetNodePostion(n32 a_nIdx);
		void ClearAccelaration();
		void Update(f32 a_fDelatTime, const glm::vec3& a_vGravity);
		void AddForce(glm::vec3 a_vForce, n32 a_nIdx);
		CSoftBodyNode* GetNode(n32 a_nIdx);
	};
}


