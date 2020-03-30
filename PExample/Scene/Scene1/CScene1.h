#pragma once

class CScene1 : public CSceneBase
{
private:
	CGameObject* pCameraObject;

public:
	CScene1(n32 a_nSceneID);
	~CScene1();

	virtual tbool Init() override;
	virtual tbool LoadScene() override;
	virtual void ReleaseScene() override;
	virtual void Clear() override;
	virtual void Loop() override;

	CGameObject* GetCamera() { return this->pCameraObject; }
};


