#pragma once

class T_DLL_EXPORT CGameObject : public CMuffinObject
{
public:	
	CMeshRenderer* m_pMeshRenderer;
	CPhysicsAttribute m_pPhysicsAttribute;

public:
	CGameObject(u64 a_uGUID) : CMuffinObject(a_uGUID)
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

	u64 GetGUID() { return this->m_nGUID; };
	tbool InitMeshRenderer(const CMesh* a_pMesh, n32 a_nShaderProgramID);
};



