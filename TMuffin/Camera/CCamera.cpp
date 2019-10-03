#include "pch.h"

CCamera::CCamera()
{
	this->m_fFieldOfViewRadians = 0;
	this->m_fScreenRatio = 0;
	this->m_fViewDisBegin = 0;
	this->m_fViewDisEnd = 0;
	this->m_vPosition = glm::vec3(0.0, 0.0, -5.0f);
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vUpwards = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_nDepth = 0;
}

CCamera::~CCamera()
{

}
