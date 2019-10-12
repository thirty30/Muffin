#include "pch.h"

CGameObject::CGameObject()
{
	this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	TMemzero(this->m_pComponentArray, sizeof(CComponent*) * E_COMPONENT_MAX);
	TMemzero(this->m_nComponentIdx, sizeof(n32) * E_COMPONENT_MAX);
	this->InitComponentIdx();
}

CGameObject::~CGameObject()
{
	for (n32 i = E_COMPONENT_INIT; i < E_COMPONENT_MAX; i++)
	{
		if (this->m_pComponentArray[i] != NULL)
		{
			delete this->m_pComponentArray[i];
			this->m_pComponentArray[i] = NULL;
		}
	}
}

void CGameObject::RefreshColliderPostion()
{
	CBaseCollider* pBaseCollider = this->GetBaseCollider();
	if (pBaseCollider != NULL)
	{
		pBaseCollider->m_vCenter = this->m_vPosition;
	}
}

void CGameObject::InitComponentIdx()
{
	this->m_nComponentIdx[E_COMPONENT_MESH_RENDER] = 0;
	this->m_nComponentIdx[E_COMPONENT_RIGIDBODY] = 1;

	//collider
	this->m_nComponentIdx[E_COMPONENT_PLANE_COLLIDER] = 2;
	this->m_nComponentIdx[E_COMPONENT_SPHERE_COLLIDER] = 2;
	this->m_nComponentIdx[E_COMPONENT_BOX_COLLIDER] = 2;
	this->m_nComponentIdx[E_COMPONENT_MESH_COLLIDER] = 2;
}

EColliderType CGameObject::GetColliderType()
{
	CBaseCollider* pBaseCollider = this->GetBaseCollider();
	if (pBaseCollider != NULL)
	{
		return pBaseCollider->m_eColliderType;
	}
	return E_COLLIDER_TYPE_INVALID;
}
