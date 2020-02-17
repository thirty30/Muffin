#include "CFBOComponent.h"
#include "Window/CWindow.h"
#include "Graphics/CGraphicsComponent.h"
#include "GameObject/CGameObject.h"
#include "Graphics/Material/CMaterial.h"
#include "Camera/CCamera.h"
#include "Graphics/CGraphicsWorld.h"
#include "Engine/Engine.h"
#include "GameObject/CGameObject.h"

CFBOComponent::CFBOComponent()
{
	this->m_pCameraObject = NULL;
}

CFBOComponent::~CFBOComponent()
{
	if (this->m_pCameraObject != NULL)
	{
		delete m_pCameraObject;
	}
	MUFFIN.GetGraphicsWorld()->RemoveFBOObject(this);
}

void CFBOComponent::Init()
{
	MUFFIN.GetGraphicsWorld()->AddFBOObject(this);

	this->m_pCameraObject = new CGameObject();
	this->m_pCameraObject->GetTransform().m_vPosition = this->m_vCameraPosition;
	CCamera* pCamera = static_cast<CCamera*>(this->m_pCameraObject->AddComponent<CCamera>());
	pCamera->m_fFieldOfViewRadians = this->m_fFieldOfViewRadians;
	pCamera->m_fScreenRatio = this->m_fScreenRatio;
	pCamera->m_fViewDisBegin = this->m_fViewDisBegin;
	pCamera->m_fViewDisEnd = this->m_fViewDisEnd;
	pCamera->m_vTowards = glm::normalize(this->m_vTowards);
	this->m_pGraphics = static_cast<CGraphicsComponent*>(this->GetGameObject()->GetComponent<CGraphicsComponent>());

	glCreateFramebuffers(1, &this->m_nFBOID);
	//glGenFramebuffers(1, &this->m_nFBOID);	//opengl 3.5
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);

	//color texture
	glGenTextures(1, &this->m_nColorTextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_nColorTextureID);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, this->m_nWidthSize, this->m_nHeightSize);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_nWidthSize, this->m_nHeightSize, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	//depth texture
	glGenTextures(1, &this->m_nDepthTextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_nDepthTextureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, this->m_nWidthSize, this->m_nHeightSize);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->m_nColorTextureID, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->m_nDepthTextureID, 0);

	static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Init Frame Buffer Failed..." << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void CFBOComponent::Clear()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);
	glViewport(0, 0, this->m_nWidthSize, this->m_nHeightSize);
	GLfloat	fZero = 0.0f;
	GLfloat fOne = 1.0f;
	glClearBufferfv(GL_COLOR, 0, &fZero);
	glClearBufferfv(GL_DEPTH, 0, &fOne);	
	glStencilMask(0xFF);
	glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);	// Clear value for stencil
}

void CFBOComponent::BindBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);
	this->Clear();
}

void CFBOComponent::ReleaseBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	n32 nShaderID = this->m_pGraphics->GetMaterial()->GetShaderID();
	glUseProgram(nShaderID);

	GLint nULID = this->m_pGraphics->GetMaterial()->FindMaterialParam(1)->m_nULID;
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, this->m_nColorTextureID);
	glUniform1i(nULID, 0);
	//glBindTexture(GL_TEXTURE_2D, this->m_nDepthTextureID);
}

T_INLINE CCamera* CFBOComponent::GetCamera()
{
	return static_cast<CCamera*>(this->m_pCameraObject->GetComponent<CCamera>());
}
