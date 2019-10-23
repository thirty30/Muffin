#include "pch.h"

void MuffinRenderObjects()
{
	CCamera* pCamera = MUFFIN.GetCameraMgr()->GetTopCamera();
	if (pCamera == NULL)
	{
		//cout << "No Scene Camera!!" << endl;
		return;
	}
	glm::mat4 matV = pCamera->GetView();
	glm::mat4 matP = pCamera->GetPerspective();

	hash_map<u64, CGameObject*>::iterator iter = MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.begin();
	for (; iter != MUFFIN.GetGameObjectMgr()->m_mapID2GameObj.end(); iter++)
	{
		CGameObject* pCurGameObj = iter->second;
		if (pCurGameObj->IsEnable() == false)
		{
			continue;
		}
		CMeshRenderer* pMeshRenderer = pCurGameObj->GetComponent<CMeshRenderer>(E_COMPONENT_MESH_RENDER);
		if (pMeshRenderer == NULL)
		{
			continue;
		}

		glm::mat4 matM = glm::mat4(1.0f);

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), pCurGameObj->m_vPosition);
		matM *= trans;

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), pCurGameObj->m_vScale);
		matM *= scale;

		glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(pCurGameObj->m_vRotation.x), glm::vec3(1.0f, 0.0, 0.0f));
		matM *= rotateX;

		glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(pCurGameObj->m_vRotation.y), glm::vec3(0.0f, 1.0, 0.0f));
		matM *= rotateY;

		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(pCurGameObj->m_vRotation.z), glm::vec3(0.0f, 0.0, 1.0f));
		matM *= rotateZ;

		n32 nShaderProgramID = pMeshRenderer->m_nShaderProgramID;
		glUseProgram(nShaderProgramID);

		GLint nDiffuseColour = glGetUniformLocation(nShaderProgramID, "un_vDiffuseColour");
		glUniform4f(nDiffuseColour, pMeshRenderer->m_vRGB.r, pMeshRenderer->m_vRGB.g, pMeshRenderer->m_vRGB.b, 1.0f);

		GLint nSpecularColour = glGetUniformLocation(nShaderProgramID, "un_vSpecularColour");
		glUniform4f(nSpecularColour, 1.0f, 1.0f, 1.0f, 100.0f);

		GLint nEyeLocation = glGetUniformLocation(nShaderProgramID, "un_vEyeLocation");
		glUniform4f(nEyeLocation, pCamera->m_vPosition.x, pCamera->m_vPosition.y, pCamera->m_vPosition.z, 1.0f);

		MUFFIN.GetLightMgr()->RenderLights(nShaderProgramID);

		GLint matModel_UL = glGetUniformLocation(nShaderProgramID, "matModel");
		GLint matView_UL = glGetUniformLocation(nShaderProgramID, "matView");
		GLint matProj_UL = glGetUniformLocation(nShaderProgramID, "matProj");

		GLint matModelIT_UL = glGetUniformLocation(nShaderProgramID, "matModelInverseTranspose");
		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matM));
		glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

		glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matM));
		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matV));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(matP));

		glPolygonMode(GL_FRONT_AND_BACK, pMeshRenderer->m_nRenderMode);

		CMeshDrawInfo* pDrawInfo = pMeshRenderer->m_pMeshDrawInfo;
		glBindVertexArray(pDrawInfo->m_nVAOID);
		glDrawElements(GL_TRIANGLES, pDrawInfo->m_nTriangleIndexCount, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
}
