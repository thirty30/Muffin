#pragma once

class T_DLL_EXPORT CColliderCapsule : public CColliderBase
{
public:
	CColliderCapsule();
	~CColliderCapsule();

	virtual void SetScale(glm::vec3 a_vScale) {}
};
