#pragma once

class CMuffinObject
{
public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;

	CMuffinObject()
	{
		this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	virtual ~CMuffinObject(){}
};

