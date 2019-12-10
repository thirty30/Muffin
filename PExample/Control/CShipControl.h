#pragma once

class CActor;
class CShipControl : public CSingleton<CShipControl>
{
private:
	tbool m_bReadyRotateCamera;
	glm::vec2 m_vLastCursor;
	glm::vec3 m_vFrontVelocity;
	glm::vec3 m_vBackVelocity;
	glm::vec3 m_vFlankVelocity;
	glm::vec3 m_vVerticalVelocity;

public:
	CShipControl();
	~CShipControl();

	void ControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
	void ControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods);
	void ControlCursor(f64 a_fX, f64 a_fY);

	CActor* pActor;
};
