#pragma once

class T_DLL_EXPORT CGameObject
{
private:
	u64 m_nMuffinGameObectGUID;
	tbool m_bEnable;
	
	friend class CGameObjectManager;

public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vLocalPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

	CGameObject();
	virtual ~CGameObject();

	T_INLINE tbool IsEnable() { return this->m_bEnable; }
	T_INLINE void SetEnable(tbool a_bEnable) { this->m_bEnable = a_bEnable; }

	void SetRotation(glm::vec3 a_vEulerAngle);	
	void UpdateRotation(glm::vec3 a_vEulerAngle);

	void SetRotation(glm::quat a_quat);
	void UpdateRotation(glm::quat a_quat);

	glm::vec3 GetEulerAngle();
};


