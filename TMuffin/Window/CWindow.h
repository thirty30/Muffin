#pragma once
#include "TMuffinSysInclude.h"

class CWindow : public CSingleton<CWindow>
{
private:
	GLFWwindow* m_pWindow;
	n32 m_nWindowWidth;
	n32 m_nWindowHigh;
	tstring m_strWindowTitle;

public:
	CWindow()
	{
		this->m_nWindowWidth = 0;
		this->m_nWindowHigh = 0;
		this->m_strWindowTitle = "";
		this->m_pWindow = NULL;
	}
	~CWindow() {}

	tbool InitWindow(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName);
	void DrawWindow();
	void Clear();
	GLFWwindow* GetGLFWWindow() { return this->m_pWindow; }
	tbool WindowShouldClose();
	T_INLINE n32 GetWindowWidth() { return this->m_nWindowWidth; }
	T_INLINE n32 GetWindowHeight() { return this->m_nWindowHigh; }
};
