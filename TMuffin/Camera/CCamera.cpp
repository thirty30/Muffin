#include "CCamera.h"
#include "CCameraManager.h"
#include "Engine/Engine.h"
#include "GameObject/CGameObject.h"
#include "Transform/CTransform.h"


void CCamera::Init()
{
	MUFFIN.GetCameraMgr()->AddCamera(this);
}

CCamera::CCamera()
{
	this->m_fFieldOfViewRadians = 0;
	this->m_fScreenRatio = 0;
	this->m_fViewDisBegin = 0;
	this->m_fViewDisEnd = 0;
	this->m_vTowards = glm::vec3(0.0f, 0.0f, 1.0f);
	this->m_vUpwards = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_nDepth = 0;
}

CCamera::~CCamera()
{
	MUFFIN.GetCameraMgr()->RemoveCamera(this);
}

T_INLINE glm::mat4 CCamera::GetPerspective()
{
	return glm::perspective(this->m_fFieldOfViewRadians, this->m_fScreenRatio, this->m_fViewDisBegin, this->m_fViewDisEnd);
}

T_INLINE glm::mat4 CCamera::GetView()
{
	CTransform& rTrans = this->GetGameObject()->GetTransform();
	glm::vec3 vTowards = rTrans.m_vPosition + this->m_vTowards;
	//glm::quat qView = glm::quatLookAt(vTowards, this->m_vUpwards);
	return glm::lookAt(rTrans.m_vPosition, vTowards, this->m_vUpwards);
}
