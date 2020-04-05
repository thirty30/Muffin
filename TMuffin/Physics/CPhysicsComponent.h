#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/CComponentBase.h"
#include "../TPhysics/TPhysics.h"

class T_DLL_EXPORT CPhysicsComponent : public CComponentBase
{
private:
	CPhysicsObject m_phyObj;

public:
	tstring m_strBodyName;
	tbool m_bUseGravity;
	tbool m_bIsStatic;
	tstring m_strColliderName;
	glm::vec3 m_vCenter;
	glm::vec3 m_vSize;
	f32 m_fConstant;
	glm::vec3 m_vDirection;
	f32 m_fRadius;
	f32 m_fElastic;
	tbool m_bIsTrigger;
	tstring m_strTag;

	T_SCS
		T_SCP(m_strBodyName, tstring)
		T_SCP(m_bUseGravity, tbool)
		T_SCP(m_bIsStatic, tbool)
		T_SCP(m_strColliderName, tstring)
		T_SCP(m_vCenter, glm::vec3)
		T_SCP(m_vSize, glm::vec3)
		T_SCP(m_fConstant, f64)
		T_SCP(m_vDirection, glm::vec3)
		T_SCP(m_fRadius, f64)
		T_SCP(m_fElastic, f64)
		T_SCP(m_bIsTrigger, tbool)
		T_SCP(m_strTag, tstring)
	T_SCE

public:
	CPhysicsComponent();
	~CPhysicsComponent();

	CPhysicsObject& GetPhysicsObj() { return this->m_phyObj; }
	
	virtual void Init() override;
	virtual void Update() override;
};

extern void TMuffin_OnCollision(const SCollisionInfo& a_rCollision);
