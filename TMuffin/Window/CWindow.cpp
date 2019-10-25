#include "pch.h"

T_IMPLEMENT_SINGLETON(CWindow)

tbool CWindow::InitWindow(n32 a_nWinWidth, n32 a_nWinHigh, const tcchar* a_strWinName)
{
	this->m_nWindowWidth = a_nWinWidth;
	this->m_nWindowHigh = a_nWinHigh;
	this->m_strWindowTitle = a_strWinName;

	glfwSetErrorCallback(GLFWErrorCallback);
	if (glfwInit() == GLFW_FALSE)
	{
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	this->m_pWindow = glfwCreateWindow(this->m_nWindowWidth, this->m_nWindowHigh, this->m_strWindowTitle.c_str(), NULL, NULL);	//sanshi mark to know the last 2 parms
	if (this->m_pWindow == NULL)
	{
		glfwTerminate();
		return false;
	}
	glfwSetKeyCallback(this->m_pWindow, KeyCallBack);	//register key back
	glfwSetMouseButtonCallback(this->m_pWindow, MouseCallBack);
	glfwSetCursorPosCallback(this->m_pWindow, CursorCallBack);
	glfwSetScrollCallback(this->m_pWindow, ScrollCallBack);
	glfwMakeContextCurrent(this->m_pWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH);			//write to the depth buffer
	glEnable(GL_DEPTH_TEST);	//Test with buffer when drawing

	return true;
}

void CWindow::DrawWindow()
{
	n32 nWidth, nHeight = 0;
	glfwGetFramebufferSize(this->m_pWindow, &nWidth, &nHeight);
	glViewport(0, 0, nWidth, nHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear both the colour(what we see) buffer and  the depth(z) buffer

	MUFFIN.GetGraphicsRenderer()->GraphicsLoop();

	glfwSwapBuffers(this->m_pWindow);
}

void CWindow::Clear()
{
	glfwDestroyWindow(this->m_pWindow);
	this->m_pWindow = NULL;
	glfwTerminate();
}

tbool CWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(this->m_pWindow);
}


