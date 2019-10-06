#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CCameraControl)

CCameraControl::CCameraControl()
{
	this->m_bReadyRotateCamera = false;
	this->m_vLastCursor = glm::vec2(0, 0);
}

CCameraControl::~CCameraControl()
{

}

void CCameraControl::CameraControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	f32 fCameraSpeed = 0.15f;
	switch (a_nKey)
	{
	case GLFW_KEY_W:
	{
		CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
		if (pCamera == NULL)
		{
			break;
		}
		pCamera->m_vPosition.z += fCameraSpeed;
		pCamera->m_vTowards.z += fCameraSpeed;
	}
	break;
	case GLFW_KEY_A:
	{
		CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
		if (pCamera == NULL)
		{
			break;
		}
		pCamera->m_vPosition.x += fCameraSpeed;
		pCamera->m_vTowards.x += fCameraSpeed;
	}
	break;
	case GLFW_KEY_S:
	{
		CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
		if (pCamera == NULL)
		{
			break;
		}
		pCamera->m_vPosition.z -= fCameraSpeed;
		pCamera->m_vTowards.z -= fCameraSpeed;
	}
	break;
	case GLFW_KEY_D:
	{
		CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
		if (pCamera == NULL)
		{
			break;
		}
		pCamera->m_vPosition.x -= fCameraSpeed;
		pCamera->m_vTowards.x -= fCameraSpeed;
	}
	break;
	default:
		break;
	}
}

void CCameraControl::CameraControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	switch (a_nKey)
	{
	case GLFW_MOUSE_BUTTON_2:
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->m_bReadyRotateCamera = true;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->m_bReadyRotateCamera = false;
			this->m_vLastCursor = glm::vec2(0, 0);
		}
	}
	break;
	default:
		break;
	}
}

void CCameraControl::CameraControlCursor(f64 a_fX, f64 a_fY)
{
	if (this->m_bReadyRotateCamera == true)
	{
		glm::vec2 vNowCursor = glm::vec2(a_fX, a_fY);
		if (this->m_vLastCursor == glm::vec2(0, 0))
		{
			this->m_vLastCursor = vNowCursor;
		}
		if (this->m_vLastCursor != vNowCursor)
		{
			glm::vec2 vTempCursor = vNowCursor - this->m_vLastCursor;
			glm::vec2 vTorwards = glm::normalize(vTempCursor);

			CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
			if (pCamera == NULL)
			{
				return;
			}
			pCamera->m_vTowards.x -= vTorwards.x * 0.05;
			pCamera->m_vTowards.y -= vTorwards.y * 0.05;
			this->m_vLastCursor = vNowCursor;
		}
	}
}



