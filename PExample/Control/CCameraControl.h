#pragma once

class CCameraControl : public CSingleton<CCameraControl>
{
private:
	tbool m_bReadyRotateCamera;
	glm::vec2 m_vLastCursor;
public:
	CCameraControl();
	~CCameraControl();

	void CameraControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
	void CameraControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods);
	void CameraControlCursor(f64 a_fX, f64 a_fY);
};
