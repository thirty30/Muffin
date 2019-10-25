#include "pch.h"
#include "./CGraphicsRenderer.h"

CGraphicsRenderer::CGraphicsRenderer()
{
	this->m_mapID2GraphicsObj.clear();
}

CGraphicsRenderer::~CGraphicsRenderer()
{
	this->m_mapID2GraphicsObj.clear();
}

void CGraphicsRenderer::AddObject(CGraphicsObject* a_pObject)
{
	this->m_mapID2GraphicsObj[a_pObject->m_nMuffinGraphicsObectGUID] = a_pObject;
}

void CGraphicsRenderer::RemoveObject(CGraphicsObject* a_pObject)
{
	u64 nGUID = a_pObject->m_nMuffinGraphicsObectGUID;
	if (this->FindObject(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2GraphicsObj.erase(nGUID);
}

CGraphicsObject* CGraphicsRenderer::FindObject(u64 a_nGUID)
{
	hash_map<u64, CGraphicsObject*>::const_iterator iter = this->m_mapID2GraphicsObj.find(a_nGUID);
	if (iter == this->m_mapID2GraphicsObj.end())
	{
		return NULL;
	}
	return iter->second;
}

void CGraphicsRenderer::GraphicsLoop()
{
	CCamera* pCamera = MUFFIN.GetCameraMgr()->GetTopCamera();
	if (pCamera == NULL)
	{
		//cout << "No Scene Camera!!" << endl;
		return;
	}
	glm::mat4 matV = pCamera->GetView();
	glm::mat4 matP = pCamera->GetPerspective();

	hash_map<u64, CGraphicsObject*>::iterator iter = this->m_mapID2GraphicsObj.begin();
	for (; iter != this->m_mapID2GraphicsObj.end(); iter++)
	{
		CGraphicsObject* pGraphicsObj = iter->second;
		CGameObject* pGameObj = pGraphicsObj->m_pGameObject;
		if (pGameObj->IsEnable() == false)
		{
			continue;
		}

		glm::mat4 matM = glm::mat4(1.0f);

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), pGameObj->m_vPosition);
		matM *= trans;

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), pGameObj->m_vScale);
		matM *= scale;

		glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(pGameObj->m_vRotation.x), glm::vec3(1.0f, 0.0, 0.0f));
		matM *= rotateX;

		glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(pGameObj->m_vRotation.y), glm::vec3(0.0f, 1.0, 0.0f));
		matM *= rotateY;

		glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(pGameObj->m_vRotation.z), glm::vec3(0.0f, 0.0, 1.0f));
		matM *= rotateZ;

		n32 nShaderProgramID = pGraphicsObj->m_nShaderProgramID;
		glUseProgram(nShaderProgramID);

		GLint nDiffuseColour = glGetUniformLocation(nShaderProgramID, "un_vDiffuseColour");
		glUniform4f(nDiffuseColour, 1.0f, 1.0f, 1.0f, 1.0f);

		GLint nSpecularColour = glGetUniformLocation(nShaderProgramID, "un_vSpecularColour");
		glUniform4f(nSpecularColour, 1.0f, 1.0f, 1.0f, 100.0f);

		GLint nEyeLocation = glGetUniformLocation(nShaderProgramID, "un_vEyeLocation");
		glUniform4f(nEyeLocation, pCamera->m_vPosition.x, pCamera->m_vPosition.y, pCamera->m_vPosition.z, 1.0f);

		MUFFIN.GetLightMgr()->RenderLights(nShaderProgramID);

		///////////////////////////////////////////////
		//GLuint textureID = 1;
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, textureID);

		//GLint nSampler01 = glGetUniformLocation(nShaderProgramID, "textSamp01");
		//glUniform1i(nSampler01, 0);
		///////////////////////////////////////////////

		GLint matModel_UL = glGetUniformLocation(nShaderProgramID, "matModel");
		GLint matView_UL = glGetUniformLocation(nShaderProgramID, "matView");
		GLint matProj_UL = glGetUniformLocation(nShaderProgramID, "matProj");

		GLint matModelIT_UL = glGetUniformLocation(nShaderProgramID, "matModelInverseTranspose");
		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matM));
		glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

		glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matM));
		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matV));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(matP));

		glPolygonMode(GL_FRONT_AND_BACK, pGraphicsObj->m_nRenderMode);

		CMeshDrawInfo* pDrawInfo = pGraphicsObj->m_pMeshDrawInfo;
		glBindVertexArray(pDrawInfo->m_nVAOID);
		glDrawElements(GL_TRIANGLES, pDrawInfo->m_nTriangleIndexCount, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
}
