#include "pch.h"

CMaterialDefault::CMaterialDefault()
{

}

CMaterialDefault::~CMaterialDefault()
{

}
tbool CMaterialDefault::Init()
{
	n32 nShaderID = this->GetShaderProgramID();
	this->m_nULColour = glGetUniformLocation(nShaderID, "un_vColour");
	return true;
}

T_INLINE void CMaterialDefault::RenderMaterial()
{
	glCullFace(GL_BACK);
	glUniform4fv(this->m_nULColour, 1, glm::value_ptr(this->m_vRGBA));
}

T_INLINE void CMaterialDefault::SetColor(glm::vec4 a_vRGBA)
{
	this->m_vRGBA = a_vRGBA;
}
