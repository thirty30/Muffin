#pragma once 

class T_DLL_EXPORT CMaterialDefault : public CMaterialBase
{
private:
	GLuint m_nULColour;
	glm::vec4 m_vRGBA;

public:
	CMaterialDefault();
	~CMaterialDefault();

	virtual tbool Init();
	virtual T_INLINE void RenderMaterial();
	virtual T_INLINE void SetColor(glm::vec4 a_vRGBA);
};


