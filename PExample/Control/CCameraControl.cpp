#include "stdafx.h"
T_IMPLEMENT_SINGLETON(CCameraControl)

CCameraControl::CCameraControl()
{
	this->m_bMidPress = false;
	this->m_bReadyRotateCamera = false;
	this->m_vLastCursor = glm::vec2(-1, -1);
	
	this->m_fCameraYMoveSpeed = 2.2f;
	this->m_fCameraXMoveSpeed = 2.4f;
	this->m_fCameraRotationSpeed = 0.6f;
	this->m_fCameraScrollSpeed = 8.0f;

	//this->m_fCameraYMoveSpeed = 0.2f;
	//this->m_fCameraXMoveSpeed = 0.4f;
	//this->m_fCameraRotationSpeed = 0.6f;
	//this->m_fCameraScrollSpeed = 2.0f;
}

CCameraControl::~CCameraControl()
{

}

void CCameraControl::CameraControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	f32 fSpeed = 1.1f;
	f32 testspeed = 20.0f;
	switch (a_nKey)
	{
	case GLFW_KEY_1:
	{
		if (a_nAction == GLFW_PRESS)
		{
			lua_State* pL = CGame::GetSingleton().GetCurrentScene()->m_pLuaState;
			lua_getglobal(pL, "DistributeEvent");
			lua_pushnumber(pL, 1);
			lua_pcall(pL, 1, 0, 0);
		}

	}
	break;
	case GLFW_KEY_2:
	{
		if (a_nAction == GLFW_PRESS)
		{
			lua_State* pL = CGame::GetSingleton().GetCurrentScene()->m_pLuaState;
			lua_getglobal(pL, "DistributeEvent");
			lua_pushnumber(pL, 2);
			lua_pcall(pL, 1, 0, 0);
		}

	}
	break;
	case GLFW_KEY_3:
	{
		if (a_nAction == GLFW_PRESS)
		{
			lua_State* pL = CGame::GetSingleton().GetCurrentScene()->m_pLuaState;
			lua_getglobal(pL, "DistributeEvent");
			lua_pushnumber(pL, 3);
			lua_pcall(pL, 1, 0, 0);
		}

	}
	break;
	case GLFW_KEY_4:
	{
		if (a_nAction == GLFW_PRESS)
		{
			lua_State* pL = CGame::GetSingleton().GetCurrentScene()->m_pLuaState;
			lua_getglobal(pL, "DistributeEvent");
			lua_pushnumber(pL, 4);
			lua_pcall(pL, 1, 0, 0);
		}

	}
	break;
	case GLFW_KEY_5:
	{

	}
	break;
	case GLFW_KEY_6:
	{

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
			this->m_vLastCursor = glm::vec2(-1, -1);
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
			this->m_vLastCursor = glm::vec2(-1, -1);
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
		if (this->m_vLastCursor == glm::vec2(-1, -1))
		{
			this->m_vLastCursor = vNowCursor;
		}
		if (this->m_vLastCursor != vNowCursor)
		{
			glm::vec2 vTempCursor = vNowCursor - this->m_vLastCursor;
			glm::vec2 vTorwards = glm::normalize(vTempCursor);
			glm::vec4 vFront = glm::vec4(pCamera->m_vTowards, 1.0f);

			f32 fYAngle = glm::radians(this->m_fCameraRotationSpeed * (-vTorwards.x));
			glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			vFront = matRotY * vFront;
			pCamera->m_vTowards = vFront;

			f32 fXAngle = glm::radians(this->m_fCameraRotationSpeed * vTorwards.y);
			glm::mat4 matRotX = glm::rotate(glm::mat4(1.0f), fXAngle, glm::vec3(1.0f, 0.0f, 0.0f));
			vFront = matRotX * vFront;
			pCamera->m_vTowards = vFront;

			//printf("Angle: %f, towardy: %f\n", fXAngle, vTorwards.y);

			this->m_vLastCursor = vNowCursor;
		}
	}
	if (this->m_bMidPress == true)
	{
		glm::vec2 vNowCursor = glm::vec2(a_fX, a_fY);
		if (this->m_vLastCursor == glm::vec2(-1, -1))
		{
			this->m_vLastCursor = vNowCursor;
		}
		if (this->m_vLastCursor != vNowCursor)
		{
			glm::vec2 vTempCursor = vNowCursor - this->m_vLastCursor;
			glm::vec2 vTorwards = glm::normalize(vTempCursor);

			glm::vec3 vVector1 = glm::vec3(pCamera->m_vTowards.x, 0.0f, pCamera->m_vTowards.z);
			glm::vec3 vVector2 = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 vVertical = glm::cross(vVector1, vVector2);

			pCamera->m_vPosition.x += vVertical.x * this->m_fCameraXMoveSpeed * -vTorwards.x;
			pCamera->m_vPosition.y += this->m_fCameraYMoveSpeed * vTorwards.y;
			pCamera->m_vPosition.z += vVertical.z * this->m_fCameraXMoveSpeed * -vTorwards.x;
			this->m_vLastCursor = vNowCursor;
		}
	}

	//CGame::GetSingleton().GetCurrentScene()->pParticle->SetCameraPosition(pCamera->m_vPosition);
}

void CCameraControl::CameraControlScroll(f64 a_fX, f64 a_fY)
{
	CCamera* pCamera = CGame::GetSingleton().GetCurrentScene()->GetCamera();
	if (pCamera == NULL)
	{
		return;
	}
	if (a_fY > 0)
	{
		pCamera->m_vPosition += pCamera->m_vTowards * this->m_fCameraScrollSpeed;
	}
	if (a_fY < 0)
	{
		pCamera->m_vPosition += -pCamera->m_vTowards * this->m_fCameraScrollSpeed;
	}
	//CGame::GetSingleton().GetCurrentScene()->pParticle->SetCameraPosition(pCamera->m_vPosition);
}


