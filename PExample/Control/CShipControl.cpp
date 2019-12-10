#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CShipControl)

CShipControl::CShipControl()
{
	this->m_bReadyRotateCamera = false;
	this->m_vLastCursor = glm::vec2(-1, -1);

	this->m_vFrontVelocity = glm::vec3(0.0f, 0.0f, 20.0f);
	this->m_vBackVelocity = glm::vec3(0.0f, 0.0f, -20.0f);
	this->m_vFlankVelocity = glm::vec3(20.0f, 0.0f, 0.0f);
	this->m_vVerticalVelocity = glm::vec3(0.0f, 20.0f, 0.0f);
}

CShipControl::~CShipControl()
{

}

void CShipControl::ControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	if (a_nKey == GLFW_KEY_W)
	{
		this->pActor->m_vPosition.z += 1000.0f * TMuffin_GetDeltaFrameTime();
	}
	if (a_nKey == GLFW_KEY_A)
	{
		this->pActor->m_vPosition.x += 1000.0f * TMuffin_GetDeltaFrameTime();
	}
	if (a_nKey == GLFW_KEY_S)
	{
		this->pActor->m_vPosition.z -= 1000.0f * TMuffin_GetDeltaFrameTime();
	}
	if (a_nKey == GLFW_KEY_D)
	{
		this->pActor->m_vPosition.x -= 1000.0f * TMuffin_GetDeltaFrameTime();
	}
}

void CShipControl::ControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	if (a_nKey == GLFW_MOUSE_BUTTON_2)
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->m_bReadyRotateCamera = true;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->m_bReadyRotateCamera = false;
			this->m_vLastCursor = glm::vec2(-1, -1);
		}
	}
}

void CShipControl::ControlCursor(f64 a_fX, f64 a_fY)
{

}
