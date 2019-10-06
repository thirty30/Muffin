#pragma once

class CScene
{
private:
	u64 m_nSceneID;
	CCamera* m_pCamera;
	CCameraControl* m_pCameraControl;
	u64 m_nGUIDIdx;

private:
	u64 GenGUID();

public:
	CScene();
	~CScene();

	tbool Init();
	tbool LoadScene();
	void Clear();

	CCamera* GetCamera() { return this->m_pCamera; }
};


