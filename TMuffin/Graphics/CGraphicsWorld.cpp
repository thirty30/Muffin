#include "CGraphicsWorld.h"
#include "CGraphicsComponent.h"
#include "FBO/CFBOComponent.h"
#include "SkyBox/CSkyBox.h"
#include "Mesh/CMesh.h"
#include "Engine/Engine.h"
#include "Camera/CCameraManager.h"
#include "Material/CMaterial.h"
#include "Camera/CCamera.h"
#include "Utility/CGUIDMaker.h"
#include "Light/CLightManager.h"
#include "Window/CWindow.h"

CGraphicsWorld::CGraphicsWorld()
{
	this->m_mapID2GraphicsObj.clear();
	this->m_mapID2FBOObj.clear();
	this->m_pSkyBox = NULL;
}

CGraphicsWorld::~CGraphicsWorld()
{
	this->m_mapID2GraphicsObj.clear();
	this->m_mapID2FBOObj.clear();
}

void CGraphicsWorld::AddGraphicsObject(CGraphicsComponent* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	this->m_mapID2GraphicsObj[nGUID] = a_pComponent;
}

void CGraphicsWorld::RemoveGraphicsObject(CGraphicsComponent* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	if (this->FindObject(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2GraphicsObj.erase(nGUID);
}

CGraphicsComponent* CGraphicsWorld::FindObject(u64 a_nGUID)
{
	hash_map<u64, CGraphicsComponent*>::const_iterator iter = this->m_mapID2GraphicsObj.find(a_nGUID);
	if (iter == this->m_mapID2GraphicsObj.end())
	{
		return NULL;
	}
	return iter->second;
}

void CGraphicsWorld::AddFBOObject(CFBOComponent* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	this->m_mapID2FBOObj[nGUID] = a_pComponent;
}

void CGraphicsWorld::RemoveFBOObject(CFBOComponent* a_pComponent)
{
	u64 nGUID = a_pComponent->GetGameObject()->GetGameObjectID();
	if (this->FindObject(nGUID) == NULL)
	{
		return;
	}
	this->m_mapID2FBOObj.erase(nGUID);
}

void CGraphicsWorld::SetSkyBox(CSkyBox* a_pSkyBox)
{
	this->m_pSkyBox = a_pSkyBox;
}

void CGraphicsWorld::GraphicsLoop()
{
	CCamera* pCamera = MUFFIN.GetCameraMgr()->GetTopCamera();
	if (pCamera == NULL)
	{
		//cout << "No Scene Camera!!" << endl;
		return;
	}
	this->RenderObject(pCamera);
	this->RenderFBO();
}

void CGraphicsWorld::RenderSkyBox(glm::mat4 a_matV, glm::mat4 a_matP)
{
	if (this->m_pSkyBox == NULL)
	{
		return;
	}

	glm::mat4 matV = a_matV;
	glm::mat4 matP = a_matP;
	glm::mat4 matM = glm::mat4(1.0f);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), this->m_pSkyBox->m_vScale);
	matM *= scale;

	n32 nShaderProgramID = this->m_pSkyBox->GetShaderID();
	glUseProgram(nShaderProgramID);

	this->m_pSkyBox->Render();

	GLint matModel_UL = glGetUniformLocation(nShaderProgramID, "matModel");
	GLint matView_UL = glGetUniformLocation(nShaderProgramID, "matView");
	GLint matProj_UL = glGetUniformLocation(nShaderProgramID, "matProj");

	GLint matModelIT_UL = glGetUniformLocation(nShaderProgramID, "matModelInverseTranspose");
	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matM));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matM));
	glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matV));
	glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(matP));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	SDrawMesh* pDrawInfo = this->m_pSkyBox->m_pDrawMesh;
	glBindVertexArray(pDrawInfo->m_nVAOID);
	glDrawElements(GL_TRIANGLES, pDrawInfo->m_nTriangleIndexCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void CGraphicsWorld::RenderObject(CCamera* a_pCamera)
{
	glm::mat4 matV = a_pCamera->GetView();
	glm::mat4 matP = a_pCamera->GetPerspective();

	this->RenderSkyBox(matV, matP);

	hash_map<u64, CGraphicsComponent*>::iterator iter = this->m_mapID2GraphicsObj.begin();
	for (; iter != this->m_mapID2GraphicsObj.end(); iter++)
	{
		CGraphicsComponent* pGraphicsComponent = iter->second;
		CGameObject* pGameObj = pGraphicsComponent->GetGameObject();
		if (pGameObj->IsEnable() == false)
		{
			continue;
		}

		glm::mat4 matM = glm::mat4(1.0f);
		CTransform& rTrans = pGameObj->GetTransform();

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), rTrans.m_vPosition);
		glm::mat4 rotation = glm::mat4(rTrans.m_qRotation);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), rTrans.m_vScale);

		matM *= trans;
		matM *= rotation;
		matM *= scale;

		n32 nShaderProgramID = pGraphicsComponent->m_pMaterial->GetShaderID();
		glUseProgram(nShaderProgramID);

		GLint nDiffuseColour = glGetUniformLocation(nShaderProgramID, "un_vDiffuseColour");
		glUniform4f(nDiffuseColour, 1.0f, 1.0f, 1.0f, 1.0f);

		GLint nSpecularColour = glGetUniformLocation(nShaderProgramID, "un_vSpecularColour");
		glUniform4f(nSpecularColour, 1.0f, 1.0f, 1.0f, 100.0f);

		GLint nEyeLocation = glGetUniformLocation(nShaderProgramID, "un_vEyeLocation");
		CTransform& rCameraTrans = a_pCamera->GetGameObject()->GetTransform();
		glUniform4f(nEyeLocation, rCameraTrans.m_vPosition.x, rCameraTrans.m_vPosition.y, rCameraTrans.m_vPosition.z, 1.0f);

		MUFFIN.GetLightMgr()->RenderLights(nShaderProgramID);
		pGraphicsComponent->GetMaterial()->RenderMaterial();

		GLint matModel_UL = glGetUniformLocation(nShaderProgramID, "matModel");
		GLint matView_UL = glGetUniformLocation(nShaderProgramID, "matView");
		GLint matProj_UL = glGetUniformLocation(nShaderProgramID, "matProj");

		GLint matModelIT_UL = glGetUniformLocation(nShaderProgramID, "matModelInverseTranspose");
		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matM));
		glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

		glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matM));
		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matV));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(matP));

		glPolygonMode(GL_FRONT_AND_BACK, pGraphicsComponent->m_nRenderMode);

		SDrawMesh* pDrawInfo = pGraphicsComponent->m_pDrawMesh;
		glBindVertexArray(pDrawInfo->m_nVAOID);
		glDrawElements(GL_TRIANGLES, pDrawInfo->m_nTriangleIndexCount, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
}

void CGraphicsWorld::RenderFBO()
{
	hash_map<u64, CFBOComponent*>::iterator iter = this->m_mapID2FBOObj.begin();
	for (; iter != this->m_mapID2FBOObj.end(); iter++)
	{
		CFBOComponent* pFBO = iter->second;
		if (pFBO == NULL)
		{
			continue;
		}
		pFBO->BindBuffer();
		this->RenderObject(pFBO->GetCamera());
		pFBO->ReleaseBuffer();
	}
}

