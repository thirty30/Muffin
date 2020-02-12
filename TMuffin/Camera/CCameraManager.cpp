#include "./CCameraManager.h"

CCameraManager::CCameraManager()
{
	this->m_pSceneCamera = NULL;
}

CCameraManager::~CCameraManager()
{
	delete this->m_pSceneCamera;
	this->m_pSceneCamera = NULL;
}

T_INLINE void CCameraManager::AddCamera(CCamera* a_pCamera)
{
	this->m_pSceneCamera = a_pCamera;
}

T_INLINE void CCameraManager::RemoveCamera(CCamera* a_pCamera)
{
	delete this->m_pSceneCamera;
	this->m_pSceneCamera = NULL;
}

T_INLINE CCamera* CCameraManager::GetTopCamera()
{
	return m_pSceneCamera;
}
