#pragma once

class CCameraManager
{
private:
	CCamera* m_pCamera;
public:
	CCameraManager() 
	{
		this->m_pCamera = NULL;
	};
	~CCameraManager() {};

	inline void AddCamera(CCamera* a_pCamera) { m_pCamera = a_pCamera; }
	inline CCamera* GetTopCamera() { return m_pCamera; }
};




