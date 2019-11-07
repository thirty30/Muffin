#pragma once

class T_DLL_EXPORT CColliderSphere : public CColliderBase
{
private:
	f32 m_fRadius;

public:
	CColliderSphere();
	~CColliderSphere();

	T_INLINE void SetRadius(f32 a_fRadius);
	T_INLINE f32 GetRadius();

	virtual void SetScale(glm::vec3 a_vScale);
};



