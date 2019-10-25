#pragma once

class T_DLL_EXPORT CGameObject
{
private:
	u64 m_nMuffinGameObectGUID;
	tbool m_bEnable;
	
	friend class CGameObjectManager;

public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;

	CGameObject();
	virtual ~CGameObject();

	T_INLINE tbool IsEnable() { return this->m_bEnable; }
	T_INLINE void SetEnable(tbool a_bEnable) { this->m_bEnable = a_bEnable; }
};


