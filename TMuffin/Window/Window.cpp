#include "pch.h"

T_IMPLEMENT_SINGLETON(CWindow)

void CWindow::ErrorCallback(n32 a_nErrorCode, const gcchar* a_strDesc)
{
	printf("Error Code: %d, Error: %s\n", a_nErrorCode, a_strDesc);
}

void CWindow::KeyCallback(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{

}

gbool CWindow::InitWindow()
{
	glfwSetErrorCallback(CWindow::ErrorCallback);
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
	//register key back
	glfwSetKeyCallback(this->m_pWindow, CWindow::KeyCallback);

	glfwMakeContextCurrent(this->m_pWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	return true;
}

void CWindow::Clear()
{
	glfwDestroyWindow(this->m_pWindow);
	this->m_pWindow = NULL;
	glfwTerminate();
}
