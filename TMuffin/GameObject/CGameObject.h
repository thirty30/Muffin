#pragma once

class T_DLL_EXPORT CGameObject
{
public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec4 m_vRGBA;
	glm::vec3 m_vScale;

	tstring m_strMeshName;
	n32 m_nShaderProgramID;

	CModelDrawInfo* m_pDrawInfo;

public:
	CGameObject()
	{
		this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		this->m_vRGBA = glm::vec4(0.2f, 1.0f, 0.4f, 1.0f);
		this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);

		this->m_strMeshName = "";
	}
};



