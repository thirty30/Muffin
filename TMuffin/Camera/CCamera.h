#pragma once

class T_DLL_EXPORT CCamera : public CMuffinObject
{
public:
	float m_fFieldOfViewRadians;
	float m_fScreenRatio;
	float m_fViewDisBegin;
	float m_fViewDisEnd;
	glm::vec3 m_vTowards;
	glm::vec3 m_vUpwards;

	n32 m_nDepth;
public:
	CCamera();
	~CCamera();

	inline glm::mat4 GetPerspective()
	{
		return glm::perspective(this->m_fFieldOfViewRadians, this->m_fScreenRatio, this->m_fViewDisBegin, this->m_fViewDisEnd);
	}

	inline glm::mat4 GetView()
	{
		return glm::lookAt(this->m_vPosition, this->m_vTowards, this->m_vUpwards);
	}
};

