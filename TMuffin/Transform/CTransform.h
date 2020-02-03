#pragma once
#include "TMuffinSysInclude.h"
#include "Component/IComponent.h"


class CTransform : public IComponent
{
public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vScale;
	glm::quat m_qRotation;

public:
	CTransform();
	~CTransform();

	void SetRotation(glm::vec3 a_vEulerAngle);
	void SetRotation(glm::quat a_quat);

	void UpdateRotation(glm::vec3 a_vEulerAngle);
	void UpdateRotation(glm::quat a_quat);

	glm::vec3 GetEulerAngle();
};
