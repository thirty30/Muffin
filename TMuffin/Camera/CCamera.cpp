#include "pch.h"

CCamera::CCamera(u64 a_nGUID, f32 a_fViewRadians, f32 a_fScreenRatio, f32 a_fViewDisBegin, f32 a_fViewDisEnd)
{
	this->m_fFieldOfViewRadians = a_fViewRadians;
	this->m_fScreenRatio = a_fScreenRatio;
	this->m_fViewDisBegin = a_fViewDisBegin;
	this->m_fViewDisEnd = a_fViewDisEnd;
	this->m_vPosition = glm::vec3(0.0, 0.0, 0.0f);
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
	this->m_vUpwards = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_nDepth = 0;
}

CCamera::~CCamera()
{

}
