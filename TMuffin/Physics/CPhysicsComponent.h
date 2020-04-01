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
	CPhysicsComponent();
	~CPhysicsComponent();

	CPhysicsObject& GetPhysicsObj() { return this->m_phyObj; }
	
	virtual void Init() override;
	virtual void Update() override;
};


