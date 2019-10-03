#pragma once

class T_DLL_EXPORT CGameObject : public CMuffinObject
{
public:
	glm::vec4 m_vRGBA;
	CMeshRenderer* m_pMeshRenderer;

public:
	CGameObject()
	{
		this->m_vRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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



