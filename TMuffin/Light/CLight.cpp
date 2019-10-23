#include "pch.h"

void CLight::InitGLSLName(n32 a_nIdx)
{
	TSprintf(this->m_objName.m_strLightType, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].nLightType", a_nIdx);
	TSprintf(this->m_objName.m_strEnable, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].bEnable", a_nIdx);
	TSprintf(this->m_objName.m_strPosition, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vPosition", a_nIdx);
	TSprintf(this->m_objName.m_strDiffuse, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vDiffuse", a_nIdx);
	TSprintf(this->m_objName.m_strSpecular, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vSpecular", a_nIdx);
	TSprintf(this->m_objName.m_strSpecularPower, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].fSpecularPower", a_nIdx);
	TSprintf(this->m_objName.m_strAttenuation, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vAttenuation", a_nIdx);
	TSprintf(this->m_objName.m_strDirection, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vDirection", a_nIdx);
	TSprintf(this->m_objName.m_strParm1, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vParm1", a_nIdx);
	TSprintf(this->m_objName.m_strParm2, GLSL_STRUCT_NAME_LEN, "un_LightArray[%d].vParm2", a_nIdx);
}

CLight::CLight(ELightType a_eType)
{
	this->m_eType = a_eType;
	this->m_nMuffinGUID = 0;

	this->m_bEnable = true;
	this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_vSpecularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	this->m_fSpecularPower = 0;
	TMemzero(&this->m_objName, sizeof(this->m_objName));

	MUFFIN.GetLightMgr()->AddLight(this);
}

void CLight::InitShader(n32 a_nShaderProgramID)
{
	GLint nType = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strLightType);
	GLint nEnable = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strEnable);
	GLint nPosition = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strPosition);
	GLint nDiffuse = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strDiffuse);
	GLint nSpecular = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strSpecular);
	GLint nSpecularPower = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strSpecularPower);

	glUniform1i(nType, (n32)this->m_eType);
	glUniform1i(nEnable, (n32)this->m_bEnable);
	glUniform4f(nPosition, this->m_vPosition.x, this->m_vPosition.y, this->m_vPosition.z, 1.0f);
	glUniform4f(nDiffuse, this->m_vColor.r, this->m_vColor.g, this->m_vColor.b, this->m_vColor.a);
	glUniform4f(nSpecular, this->m_vSpecularColor.r, this->m_vSpecularColor.g, this->m_vSpecularColor.b, this->m_vSpecularColor.a);
	glUniform1f(nSpecularPower, this->m_fSpecularPower);
}

void CDirectionLight::BindShader(n32 a_nShaderProgramID)
{
	GLint nDirection = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strDirection);
	glUniform4f(nDirection, this->m_vDirection.x, this->m_vDirection.y, this->m_vDirection.z, 1.0f);
}

void CPointLight::BindShader(n32 a_nShaderProgramID)
{
	GLint nAttenuation = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strAttenuation);
	glUniform4f(nAttenuation, this->m_fConstant, this->m_fLinear, this->m_fQuadratic, this->m_fDistanceCutOff);
}

void CSpotLight::BindShader(n32 a_nShaderProgramID)
{
	GLint nDirection = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strDirection);
	glUniform4f(nDirection, this->m_vDirection.x, this->m_vDirection.y, this->m_vDirection.z, 1.0f);

	GLint nAttenuation = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strAttenuation);
	glUniform4f(nAttenuation, this->m_fConstant, this->m_fLinear, this->m_fQuadratic, this->m_fDistanceCutOff);

	GLint nParm1 = glGetUniformLocation(a_nShaderProgramID, this->m_objName.m_strParm1);
	glUniform4f(nParm1, this->m_fInnerAngle, this->m_fOuterAngle, this->m_fTBD, 0.0f);
}
