#pragma once

class T_DLL_EXPORT CColliderBase
{
private:
	EColliderType m_eColliderType;
	tbool m_bIsTrigger;
	f32 m_fElastic;

protected:
	glm::vec3 m_vCenter;

public:
	CColliderBase(EColliderType a_eColliderType);
	virtual ~CColliderBase() {}

	T_INLINE EColliderType GetColliderType();
	T_INLINE void SetCenter(glm::vec3 a_vPosition);
	T_INLINE glm::vec3 GetCenter();
	T_INLINE void SetTrigger(tbool a_bValue);
	T_INLINE tbool IsTrigger();
	T_INLINE void SetElastic(f32 a_fElastic);
	T_INLINE f32 GetElastic();

	// pure virtal function
	virtual void SetScale(glm::vec3 a_vScale) T_PURE;
};


