#pragma once

class CWindow : public CSingleton<CWindow>
{
private:
	GLFWwindow* m_pWindow;
	n32 m_nWindowWidth;
	n32 m_nWindowHigh;
	tstring m_strWindowTitle;

public:
	static void ErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc);
	static void KeyCallback(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
public:
	CWindow(n32 a_nWinWidth, n32 a_nWinHigh, tstring a_strWinName) :
		m_nWindowWidth(a_nWinWidth),
		m_nWindowHigh(a_nWinHigh),
		m_strWindowTitle(a_strWinName)
	{
		this->m_pWindow = NULL;
	}
	~CWindow() {}

	tbool InitWindow();
	void Loop();
	void Clear();
};

