#pragma once

class T_DLL_EXPORT CGameObject : public CMuffinObject
{
public:
	CMeshRenderer* m_pMeshRenderer;
	CPhysicsAttribute m_pPhysicsAttribute;

public:
	CGameObject()
	{
		this->m_pMeshRenderer = NULL;
	}

	~CGameObject()
	{
		if (this->m_pMeshRenderer != NULL)
		{
			delete this->m_pMeshRenderer;
		}
	}

	tbool InitMeshRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID);
};



