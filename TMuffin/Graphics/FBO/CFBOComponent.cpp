#include "CFBOComponent.h"
#include "Window/CWindow.h"
#include "Graphics/CGraphicsComponent.h"
#include "GameObject/CGameObject.h"
#include "Graphics/Material/CMaterial.h"
#include "Camera/CCamera.h"

CFBOComponent::CFBOComponent()
{

}

CFBOComponent::~CFBOComponent()
{
	if (this->m_pCamera != NULL)
	{
		delete m_pCamera;
	}
}

void CFBOComponent::Init()
{
	this->m_pCamera = new CCamera();
	this->m_pCamera->m_fFieldOfViewRadians = this->m_fFieldOfViewRadians;
	this->m_pCamera->m_fScreenRatio = this->m_fScreenRatio;
	this->m_pCamera->m_fViewDisBegin = this->m_fViewDisBegin;
	this->m_pCamera->m_fViewDisEnd = this->m_fViewDisEnd;
	this->m_pCamera->m_vTowards = glm::normalize(this->m_vTowards);

	glCreateFramebuffers(1, &this->m_nFBOID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);

	glGenTextures(1, &this->m_nColorTextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_nColorTextureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, this->m_nWidthSize, this->m_nHeightSize);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &this->m_nDepthTextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_nDepthTextureID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, this->m_nWidthSize, this->m_nHeightSize);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->m_nColorTextureID, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->m_nDepthTextureID, 0);

	static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// Point back to default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);

	glViewport(0, 0, this->m_nWidthSize, this->m_nHeightSize);
	GLfloat	fZero = 0.0f;
	GLfloat fOne = 1.0f;
	glClearBufferfv(GL_COLOR, 0, &fZero);
	glClearBufferfv(GL_DEPTH, 0, &fOne);
}

void CFBOComponent::BindBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_nFBOID);
}

void CFBOComponent::ReleaseBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	n32 nWidth = CWindow::GetSingleton().GetWindowWidth();
	n32 nHeight = CWindow::GetSingleton().GetWindowHeight();
	glViewport(0, 0, nWidth, nHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CGraphicsComponent* pGraphics = static_cast<CGraphicsComponent*>(this->GetGameObject()->GetComponent<CGraphicsComponent>());
	n32 nShaderID = pGraphics->GetMaterial()->GetShaderID();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_nColorTextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_nDepthTextureID);
	GLint textSamp00_UL = glGetUniformLocation(nShaderID, "secondPassColourTexture");
	glUniform1i(textSamp00_UL, 0);
}
