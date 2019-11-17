#include "pch.h"

CMaterialStandard::CMaterialStandard()
{
	this->m_vDiffuseRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_nULDiffuseColour = 0;

	this->m_vSpecularRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_nULSpecularColour = 0;

	this->m_nTextureCount = 0;
	TMemzero(this->m_TextureArray, sizeof(CTexture*) * TEXTURE_MAX_COUNT);

	this->m_nULSamplerCount = 0;
	TMemzero(this->m_nULSamplerArray, sizeof(GLint) * TEXTURE_MAX_COUNT);
}

CMaterialStandard::~CMaterialStandard()
{

}

tbool CMaterialStandard::Init()
{
	n32 nShaderID = this->GetShaderProgramID();
	this->m_nULDiffuseColour = glGetUniformLocation(nShaderID, "un_vDiffuseColour");
	this->m_nULSpecularColour = glGetUniformLocation(nShaderID, "un_vSpecularColour");
	this->m_nULSamplerCount = glGetUniformLocation(nShaderID, "un_samplerCount");

	for (n32 i = 0; i < TEXTURE_MAX_COUNT; i++)
	{
		tcchar strKey[16] = { 0 };
		TSprintf(strKey, 16, "un_Samplers[%d]", i);
		this->m_nULSamplerArray[i] = glGetUniformLocation(nShaderID, strKey);
	}
	return true;
}

T_INLINE void CMaterialStandard::RenderMaterial()
{
	glCullFace(GL_BACK);
	glUniform4fv(this->m_nULDiffuseColour, 1, glm::value_ptr(this->m_vDiffuseRGBA));
	glUniform4fv(this->m_nULSpecularColour, 1, glm::value_ptr(this->m_vSpecularRGBA));

	glUniform1i(this->m_nULSamplerCount, this->m_nTextureCount);
	for (n32 i = 0; i < this->m_nTextureCount; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->m_TextureArray[i]->GetTextureID());
		glUniform1i(this->m_nULSamplerArray[i], i);
	}
}

tbool CMaterialStandard::AddTexture(CTexture* a_pTexture)
{
	if (this->m_nTextureCount >= TEXTURE_MAX_COUNT)
	{
		return false;
	}
	this->m_TextureArray[this->m_nTextureCount] = a_pTexture;
	this->m_nTextureCount++;
}

T_INLINE n32 CMaterialStandard::GetTextureCount()
{
	return this->m_nTextureCount;
}

T_INLINE void CMaterialStandard::SetDiffuseRGBA(glm::vec4 a_vRGBA)
{
	this->m_vDiffuseRGBA = a_vRGBA;
}

T_INLINE void CMaterialStandard::SetSpecularRGBA(glm::vec4 a_vRGBA)
{
	this->m_vSpecularRGBA = a_vRGBA;
}
