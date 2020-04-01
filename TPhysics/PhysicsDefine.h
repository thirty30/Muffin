#pragma once
#include "TPhysicsInclude.h"

namespace TPhysics
{
#define GRAVITY_ACCELERATION glm::vec3(0.0f, -9.8f, 0.0f)

	enum EColliderType
	{
		E_NULL_COLLIDER = -1,

		E_PLANE_COLLIDER,
		E_SPHERE_COLLIDER,
		E_BOX_COLLIDER,
		E_CLOTH_COLLIDER,
	};

	enum EBodyType
	{
		E_NULL_BODY = -1,
		E_RIGID_BODY,
		E_SOFT_BODY
	};

	struct SCollisionResult
	{
		tbool m_bIsHit;
		glm::vec3 m_vHitPoint;
		glm::vec3 m_vHitNormal;
		f32 m_fIntersectDis;

		SCollisionResult()
		{
			this->m_bIsHit = false;
			this->m_vHitPoint = glm::vec3(0, 0, 0);
			this->m_vHitNormal = glm::vec3(0, 0, 0);
			this->m_fIntersectDis = 0;
		}
	};

	class CPhysicsObject;
	struct SCollisionCallBackInfo
	{
		CPhysicsObject* m_pSrc;
		CPhysicsObject* m_pTar;
		glm::vec3 m_vHitPoint;
		glm::vec3 m_vHitNormal;
		f32 m_fIntersectDis;
	};

	struct SCollisionInfo
	{
		CPhysicsObject* m_pTarget;
		glm::vec3 m_vHitNormal;
		glm::vec3 m_vHitPoint;
		f32 m_fIntersectDis;
	};

	struct SClothInfo
	{
		glm::vec3 m_vCornerA;
		glm::vec3 m_vCornerB;
		glm::vec3 m_vDownDir;
		n32 m_nNodeNumAcross;
		n32 m_nNodeNumDown;
		f32 m_fNodeMass;
		f32 m_fSpringConstant;
	};
}

using namespace TPhysics;
