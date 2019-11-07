#pragma once

class T_DLL_EXPORT CColliderBox : public CColliderBase
{
public:
	glm::vec3 m_vSize;

	CColliderBox();
	~CColliderBox();

	T_INLINE glm::vec3 GetMinPoint();
	T_INLINE glm::vec3 GetMaxPoint();
	T_INLINE void SetSize(glm::vec3 a_vSize);

	virtual void SetScale(glm::vec3 a_vScale);
};
