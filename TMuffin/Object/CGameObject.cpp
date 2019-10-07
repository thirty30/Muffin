#include "pch.h"

tbool CGameObject::InitMeshRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID)
{
	return this->m_pMeshRenderer.InitRenderer(a_pMesh, a_nShaderProgramID);
}
