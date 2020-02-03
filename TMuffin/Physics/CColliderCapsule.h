#pragma once
#include "TMuffinSysInclude.h"
#include "CColliderBase.h"


class T_DLL_EXPORT CColliderCapsule : public CColliderBase
{
public:
	CColliderCapsule();
	~CColliderCapsule();

	virtual void SetScale(glm::vec3 a_vScale) {}
};
