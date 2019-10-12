#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CCameraControl)

CCameraControl::CCameraControl()
{
	this->m_bMidPress = false;
	this->m_bReadyRotateCamera = false;
	this->m_vLastCursor = glm::vec2(0, 0);
	this->m_fCameraMoveSpeed = 1.0f;
	this->m_fCameraRotationSpeed = 0.5f;
}

CCameraControl::~CCameraControl()
{

}

void CCameraControl::CameraControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	/*
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
	*/
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
	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (a_nAction == GLFW_PRESS)
		{
			this->m_bMidPress = true;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			this->m_bMidPress = false;
		}
	}
	break;
	default:
		break;
	}
}

void CCameraControl::CameraControlCursor(f64 a_fX, f64 a_fY)
{
	CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
	if (pCamera == NULL)
	{
		return;
	}
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

			pCamera->m_vPosition.x += vTorwards.x * this->m_fCameraRotationSpeed;
			pCamera->m_vPosition.y += vTorwards.y * this->m_fCameraRotationSpeed;

			//pCamera->m_vTowards.x -= vTorwards.x * this->m_fCameraRotationSpeed;
			//pCamera->m_vTowards.y -= vTorwards.y * this->m_fCameraRotationSpeed;
			//this->m_vLastCursor = vNowCursor;

			//glm::mat4 matM = glm::mat4(1.0f);
			//glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(vTorwards.x * this->m_fCameraRotationSpeed), glm::vec3(1.0f, 0.0, 0.0f));
			//matM *= rotateX;

			//glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(vTorwards.y * this->m_fCameraRotationSpeed), glm::vec3(0.0f, 1.0, 0.0f));
			//matM *= rotateY;

		}
	}
	if (this->m_bMidPress == true)
	{

	}
}

void CCameraControl::CameraControlScroll(f64 a_fX, f64 a_fY)
{
	CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
	if (pCamera == NULL)
	{
		return;
	}
	glm::vec3 vTowards = glm::normalize(pCamera->m_vTowards - pCamera->m_vPosition);

	if (a_fY > 0)
	{
		pCamera->m_vPosition += vTowards * this->m_fCameraMoveSpeed;
		//pCamera->m_vPosition.z += this->m_fCameraMoveSpeed;
		//pCamera->m_vTowards.z += this->m_fCameraMoveSpeed;
	}
	if (a_fY < 0)
	{
		pCamera->m_vPosition += -vTowards * this->m_fCameraMoveSpeed;
		//pCamera->m_vPosition.z -= this->m_fCameraMoveSpeed;
		//pCamera->m_vTowards.z -= this->m_fCameraMoveSpeed;
	}
}


