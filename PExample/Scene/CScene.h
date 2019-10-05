#pragma once

class CScene
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();

	CCamera* GetCamera() { return this->m_pCamera; }
};


