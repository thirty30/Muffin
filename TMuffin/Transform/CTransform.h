#pragma once
#include "TMuffinSysInclude.h"

class T_DLL_EXPORT CTransform
{
public:
	glm::vec3 m_vPosition;
	glm::quat m_qRotation;
	glm::vec3 m_vScale;

public:
	CTransform();
	~CTransform();

	void SetRotation(glm::vec3 a_vEulerAngle);
	void SetRotation(glm::quat a_qQuaternion);

	void UpdateRotation(glm::vec3 a_vEulerAngle);
	void UpdateRotation(glm::quat a_qQuaternion);

	glm::vec3 GetEulerAngle();
};
