#include "pch.h"

T_IMPLEMENT_SINGLETON(CWindow)

void CWindow::ErrorCallback(n32 a_nErrorCode, const tcchar* a_strDesc)
{

}

void CWindow::KeyCallback(GLFWwindow* a_pWindow, n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{

}

tbool CWindow::InitWindow()
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
	glEnable(GL_DEPTH);			//write to the depth buffer
	glEnable(GL_DEPTH_TEST);	//Test with buffer when drawing
	return true;
}

void CWindow::Loop()
{
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	CCamera* pCamera = pMuffinCameraManager->GetTopCamera();
	if (pCamera == NULL)
	{
		return;
	}

	while (glfwWindowShouldClose(this->m_pWindow) == false)
	{
		//if (glfwGetKey(window, GLFW_KEY_P) == true)
		//{
		//	printf("P\n");
		//}

		//n32 nWidth, nHeight = 0;
		//glfwGetFramebufferSize(this->m_pWindow, &nWidth, &nHeight);
		//glViewport(0, 0, nWidth, nHeight);

		glViewport(0, 0, this->m_nWindowWidth, this->m_nWindowHigh);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear both the colour(what we see) buffer and  the depth(z) buffer
		
		glm::mat4 matV = pCamera->GetView();
		glm::mat4 matP = pCamera->GetPerspective();

		for (int i = 0; i < CGameObjectManager::GetSingleton().m_vList.size(); i++)
		{
			CGameObject* pCurGameObj = CGameObjectManager::GetSingleton().m_vList[i];
			glm::mat4 matM = glm::mat4(1.0f);

			glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), pCurGameObj->m_vRotation.x, glm::vec3(1.0f, 0.0, 0.0f));
			matM *= rotateX;

			glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), pCurGameObj->m_vRotation.y, glm::vec3(0.0f, 1.0, 0.0f));
			matM *= rotateY;

			glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), pCurGameObj->m_vRotation.z, glm::vec3(0.0f, 0.0, 1.0f));
			matM *= rotateZ;

			glm::mat4 trans = glm::translate(glm::mat4(1.0f), pCurGameObj->m_vPosition);
			matM *= trans;

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), pCurGameObj->m_vScale);
			matM *= scale;

			n32 nShaderProgramID = pCurGameObj->m_pMeshRenderer->m_nShaderProgramID;
			glUseProgram(nShaderProgramID);
			//GLint mvp_location = glGetUniformLocation(nShaderProgramID, "MVP");
			//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
			//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(matMVP));

			GLint matModel_UL = glGetUniformLocation(nShaderProgramID, "matModel");
			GLint matView_UL = glGetUniformLocation(nShaderProgramID, "matView");
			GLint matProj_UL = glGetUniformLocation(nShaderProgramID, "matProj");
			glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matM));
			glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matV));
			glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(matP));

			//GLint newColour_location = glGetUniformLocation(shaderProgID, "newColour");
			//glUniform3f(newColour_location, pGameObj->mRGBA.r, pGameObj->mRGBA.g, pGameObj->mRGBA.b);

			GLint newColourR_location = glGetUniformLocation(nShaderProgramID, "newColourR");
			GLint newColourG_location = glGetUniformLocation(nShaderProgramID, "newColourG");
			GLint newColourB_location = glGetUniformLocation(nShaderProgramID, "newColourB");
			glUniform1f(newColourG_location, pCurGameObj->m_vRGBA.g);
			glUniform1f(newColourB_location, pCurGameObj->m_vRGBA.b);
			glUniform1f(newColourR_location, pCurGameObj->m_vRGBA.r);

			GLint lightPosition_UL = glGetUniformLocation(nShaderProgramID, "lightPosition");
			glUniform3f(lightPosition_UL, lightPos.x, lightPos.y, lightPos.z);


			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			CMeshDrawInfo* pDrawInfo = pCurGameObj->m_pMeshRenderer->m_pMeshDrawInfo;
			glBindVertexArray(pDrawInfo->m_nVAOID);
			glDrawElements(GL_TRIANGLES, pDrawInfo->m_nTriangelIndexCount, GL_UNSIGNED_INT, NULL);
			glBindVertexArray(0);
		}
		glfwSwapBuffers(this->m_pWindow);
		glfwPollEvents();
	}
}

void CWindow::Clear()
{
	glfwDestroyWindow(this->m_pWindow);
	this->m_pWindow = NULL;
	glfwTerminate();
}
