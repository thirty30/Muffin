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

public:
	CWindow()
	{
		this->m_nWindowWidth = 0;
		this->m_nWindowHigh = 0;
		this->m_strWindowTitle = "";
		this->m_pWindow = NULL;
	}
	~CWindow() {}

	tbool InitWindow(n32 a_nWinWidth, n32 a_nWinHigh, tstring a_strWinName);
	void DrawWindow();
	void Clear();
	GLFWwindow* GetGLFWWindow() { return this->m_pWindow; }
	tbool WindowShouldClose();
};

