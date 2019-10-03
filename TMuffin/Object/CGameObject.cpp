#include "pch.h"

tbool CGameObject::InitMeshRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID)
{
	if (this->m_pMeshRenderer != NULL)
	{
		return false;
	}
	this->m_pMeshRenderer = new CMeshRenderer();
	return this->m_pMeshRenderer->InitRenderer(a_pMesh, a_nShaderProgramID);
}
