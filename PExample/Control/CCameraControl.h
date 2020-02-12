#pragma once

class CCameraControl : public CControlBase
{
private:
	tbool m_bMidPress;
	tbool m_bReadyRotateCamera;
	glm::vec2 m_vLastCursor;
	CCamera* m_pCamera;

public:
	f32 m_fCameraYMoveSpeed;
	f32 m_fCameraXMoveSpeed;
	f32 m_fCameraRotationSpeed;
	f32 m_fCameraScrollSpeed;

public:
	CCameraControl();
	~CCameraControl();

	T_INLINE void SetCamera(CCamera* a_pCamera) { this->m_pCamera = a_pCamera; }

	virtual void KeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods) override;
	virtual void MouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods) override;
	virtual void CursorEvent(f64 a_fX, f64 a_fY) override;
	virtual void ScrollEvent(f64 a_fX, f64 a_fY) override;

};
