#pragma once

class T_DLL_EXPORT CGameObject
{
private:
	u64 m_nMuffinEngineGUID;
	CComponent* m_pComponentArray[E_COMPONENT_MAX];
	n32 m_nComponentIdx[E_COMPONENT_MAX];

private:
	void RefreshColliderPostion();
	void InitComponentIdx();
	n32 GetComponentIdxByType(EComponentType a_eType) { return this->m_nComponentIdx[a_eType]; }
	CBaseCollider* GetBaseCollider() { return dynamic_cast<CBaseCollider*>(this->m_pComponentArray[2]); }

public:
	friend class CGameObjectManager;
	friend class CObjectPhysics;

	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;

	CGameObject();
	virtual ~CGameObject();

	EColliderType GetColliderType();

	template <typename T>
	T* AddComponent(EComponentType a_eType)
	{
		n32 nIdx = this->GetComponentIdxByType(a_eType);
		if (nIdx == -1)
		{
			return NULL;
		}
		if (this->m_pComponentArray[nIdx] == NULL)
		{
			this->m_pComponentArray[nIdx] = new T();
		}
		return dynamic_cast<T*>(this->m_pComponentArray[nIdx]);
	}

	template <typename T>
	T* GetComponent(EComponentType a_eType)
	{
		n32 nIdx = this->GetComponentIdxByType(a_eType);
		if (nIdx == -1)
		{
			return NULL;
		}
		return dynamic_cast<T*>(this->m_pComponentArray[nIdx]);
	}
};


