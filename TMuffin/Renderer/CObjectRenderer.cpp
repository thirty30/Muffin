#include "pch.h"

T_IMPLEMENT_SINGLETON(CObjectRenderer)

void CObjectRenderer::RenderObjects()
{
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 10.0f);
	CCamera* pCamera = pMuffinCameraManager->GetTopCamera();
	if (pCamera == NULL)
	{
		cout << "No Camera!!" << endl;
		return;
	}
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
}
