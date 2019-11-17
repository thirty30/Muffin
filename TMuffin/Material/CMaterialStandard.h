#pragma once

class T_DLL_EXPORT CMaterialStandard : public CMaterialBase
{
#define TEXTURE_MAX_COUNT 16

private:
	glm::vec4 m_vDiffuseRGBA;
	GLint m_nULDiffuseColour;

	glm::vec4 m_vSpecularRGBA;
	GLint m_nULSpecularColour;

	n32 m_nTextureCount;
	CTexture* m_TextureArray[TEXTURE_MAX_COUNT];

	GLint m_nULSamplerCount;
	GLint m_nULSamplerArray[TEXTURE_MAX_COUNT];

public:
	CMaterialStandard();
	~CMaterialStandard();

	virtual tbool Init();
	virtual T_INLINE void RenderMaterial();
	tbool AddTexture(CTexture* a_pTexture);
	T_INLINE n32 GetTextureCount();

	T_INLINE void SetDiffuseRGBA(glm::vec4 a_vRGBA);
	T_INLINE void SetSpecularRGBA(glm::vec4 a_vRGBA);

};

