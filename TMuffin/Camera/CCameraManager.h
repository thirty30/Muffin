#pragma once

class CCameraManager
{
private:
	CCamera* m_pSceneCamera;
public:
	CCameraManager() 
	{
		this->m_pSceneCamera = NULL;
	};
	~CCameraManager() {};

	inline void AddCamera(CCamera* a_pCamera) { m_pSceneCamera = a_pCamera; }
	inline CCamera* GetTopCamera() { return m_pSceneCamera; }
};




