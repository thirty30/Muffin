#pragma once

class T_DLL_EXPORT CColliderPlane : public CColliderBase
{
private:
	EPLaneColliderAxis m_eAxis;

public:
	CColliderPlane();
	~CColliderPlane();

	T_INLINE void SetAxis(EPLaneColliderAxis a_eValue);
	T_INLINE EPLaneColliderAxis GetAxis();

	virtual void SetScale(glm::vec3 a_vScale) {}
};
