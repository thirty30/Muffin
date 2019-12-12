#pragma once

class CShipControl : public CSingleton<CShipControl>
{
public:
	CShipControl();
	~CShipControl();

	void ControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
};
