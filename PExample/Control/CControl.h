#pragma once

extern void ControlKeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
extern void ControlMouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods);
extern void ControlCursorEvent(f64 a_fX, f64 a_fY);
extern void ControlScrollEvent(f64 a_fX, f64 a_fY);

class CControlBase
{
public:
	CControlBase() {}
	virtual ~CControlBase() {}

	virtual void KeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods) T_PURE;
	virtual void MouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods) T_PURE;
	virtual void CursorEvent(f64 a_fX, f64 a_fY) T_PURE;
	virtual void ScrollEvent(f64 a_fX, f64 a_fY) T_PURE;
};


class CControlManager
{
private:
	vector<CControlBase*> m_vecControls;

public:
	CControlManager();
	~CControlManager();

	template<typename T>
	CControlBase* CreateController();

	void KeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
	void MouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods);
	void CursorEvent(f64 a_fX, f64 a_fY);
	void ScrollEvent(f64 a_fX, f64 a_fY);
};

template<typename T>
CControlBase* CControlManager::CreateController()
{
	CControlBase* pController = new T();
	this->m_vecControls.push_back(pController);
	return pController;
}

