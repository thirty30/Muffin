#include "./CCameraManager.h"

CCameraManager::CCameraManager()
{
	this->m_pSceneCamera.clear();
}

CCameraManager::~CCameraManager()
{
	//for (n32 i = 0; i < this->m_pSceneCamera.size(); i++)
	//{
		//delete this->m_pSceneCamera[i];
	//}
	this->m_pSceneCamera.clear();
}

T_INLINE void CCameraManager::AddCamera(CCamera* a_pCamera)
{
	this->m_pSceneCamera.push_back(a_pCamera);
}

T_INLINE void CCameraManager::RemoveCamera(CCamera* a_pCamera)
{

}

T_INLINE CCamera* CCameraManager::GetTopCamera()
{
	if (this->m_pSceneCamera.size() <= 0)
	{
		return NULL;
	}
	return this->m_pSceneCamera[0];
}
