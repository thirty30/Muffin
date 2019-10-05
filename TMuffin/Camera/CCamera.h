#pragma once

class T_DLL_EXPORT CCamera : public CMuffinObject
{
public:
	f32 m_fFieldOfViewRadians;
	f32 m_fScreenRatio;
	f32 m_fViewDisBegin;
	f32 m_fViewDisEnd;
	glm::vec3 m_vTowards;
	glm::vec3 m_vUpwards;

	n32 m_nDepth;
public:
	CCamera(f32 a_fViewRadians, f32 a_fScreenRatio, f32 a_fViewDisBegin, f32 a_fViewDisEnd);
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

