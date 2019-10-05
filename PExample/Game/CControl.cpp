#include "stdafx.h"

void ControlKeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	f32 fCameraSpeed = 0.2f;
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

tbool bReadyRotateCamera = false;
glm::vec2 vOriginCursor = glm::vec2(-1, -1);

void ControlMouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	switch (a_nKey)
	{
	case GLFW_MOUSE_BUTTON_2:
	{
		if (a_nAction == GLFW_PRESS)
		{
			bReadyRotateCamera = true;
		}
		if (a_nAction == GLFW_RELEASE)
		{
			bReadyRotateCamera = false;
			vOriginCursor = glm::vec2(-1, -1);
		}
	}
	break;
	default:
		break;
	}
}

void ControlCursorEvent(f64 a_fX, f64 a_fY)
{
	if (bReadyRotateCamera == true)
	{
		if (vOriginCursor.x < 0)
		{
			vOriginCursor = glm::vec2(a_fX, a_fY);
		}
		glm::vec2 vNewCursor = glm::vec2(a_fX, a_fY);
		glm::vec2 vTempCursor = vNewCursor - vOriginCursor;
		if (vTempCursor == glm::vec2(0, 0))
		{
			return;
		}
		glm::vec2 vTorwards = glm::normalize(vTempCursor);

		CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
		if (pCamera == NULL)
		{
			return;
		}
		pCamera->m_vTowards.x -= vTorwards.x * 0.03;
		pCamera->m_vTowards.y -= vTorwards.y * 0.03;
	}
}
