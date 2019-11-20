#pragma once

class T_DLL_EXPORT CMaterialBase
{
private:
	n32 m_nShaderProgramID;

public:
	CMaterialBase();
	virtual ~CMaterialBase();

	T_INLINE void SetShaderProgramID(n32 a_nShaderProgramID);
	T_INLINE n32 GetShaderProgramID();

	virtual tbool Init() T_PURE;
	virtual T_INLINE void RenderMaterial() {}
	virtual void SetTexture(n32 a_nIDX, CTexture* a_pTexture) {}
	virtual T_INLINE void SetColor(glm::vec4 a_vRGBA) {}
};


