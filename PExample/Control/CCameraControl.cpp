#include "stdafx.h"

CCameraControl::CCameraControl()
{
	this->m_bMidPress = false;
	this->m_bReadyRotateCamera = false;
	this->m_vLastCursor = glm::vec2(-1, -1);
	this->m_fCameraYMoveSpeed = 0;
	this->m_fCameraXMoveSpeed = 0;
	this->m_fCameraRotationSpeed = 0;
	this->m_fCameraScrollSpeed = 0;
}

CCameraControl::~CCameraControl()
{

}

void CCameraControl::KeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	f32 fSpeed = 1.1f;
	f32 testspeed = 20.0f;
	switch (a_nKey)
	{
	case GLFW_KEY_1:
	{
		if (a_nAction == GLFW_PRESS)
		{
		}
	}
	break;
	default:
		break;
	}

}

void CCameraControl::MouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods)
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

void CCameraControl::CursorEvent(f64 a_fX, f64 a_fY)
{
	if (this->m_pCamera == NULL)
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
			glm::vec4 vFront = glm::vec4(this->m_pCamera->m_vTowards, 1.0f);

			f32 fYAngle = glm::radians(this->m_fCameraRotationSpeed * (-vTorwards.x));
			glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f), fYAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			vFront = matRotY * vFront;
			this->m_pCamera->m_vTowards = vFront;

			f32 fXAngle = glm::radians(this->m_fCameraRotationSpeed * vTorwards.y);
			glm::mat4 matRotX = glm::rotate(glm::mat4(1.0f), fXAngle, glm::vec3(1.0f, 0.0f, 0.0f));
			vFront = matRotX * vFront;
			this->m_pCamera->m_vTowards = vFront;

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

			glm::vec3 vVector1 = glm::vec3(this->m_pCamera->m_vTowards.x, 0.0f, this->m_pCamera->m_vTowards.z);
			glm::vec3 vVector2 = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 vVertical = glm::cross(vVector1, vVector2);

			CTransform& rTrans =  this->m_pCamera->GetGameObject()->GetTransform();
			rTrans.m_vPosition.x += vVertical.x * this->m_fCameraXMoveSpeed * -vTorwards.x;
			rTrans.m_vPosition.y += this->m_fCameraYMoveSpeed * vTorwards.y;
			rTrans.m_vPosition.z += vVertical.z * this->m_fCameraXMoveSpeed * -vTorwards.x;
			this->m_vLastCursor = vNowCursor;
		}
	}
}

void CCameraControl::ScrollEvent(f64 a_fX, f64 a_fY)
{
	CTransform& rTrans = this->m_pCamera->GetGameObject()->GetTransform();
	if (this->m_pCamera == NULL)
	{
		return;
	}
	if (a_fY > 0)
	{
		rTrans.m_vPosition += this->m_pCamera->m_vTowards * this->m_fCameraScrollSpeed;
	}
	if (a_fY < 0)
	{
		rTrans.m_vPosition += -this->m_pCamera->m_vTowards * this->m_fCameraScrollSpeed;
	}
}


