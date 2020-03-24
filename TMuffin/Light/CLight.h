#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "Component/CComponentBase.h"

#define GLSL_STRUCT_NAME_LEN 64
struct sGLSLLightStructName
{
	tcchar m_strLightType[GLSL_STRUCT_NAME_LEN];
	tcchar m_strEnable[GLSL_STRUCT_NAME_LEN];
	tcchar m_strPosition[GLSL_STRUCT_NAME_LEN];
	tcchar m_strDiffuse[GLSL_STRUCT_NAME_LEN];
	tcchar m_strSpecular[GLSL_STRUCT_NAME_LEN];
	tcchar m_strSpecularPower[GLSL_STRUCT_NAME_LEN];
	tcchar m_strAttenuation[GLSL_STRUCT_NAME_LEN];
	tcchar m_strDirection[GLSL_STRUCT_NAME_LEN];
	tcchar m_strParm1[GLSL_STRUCT_NAME_LEN];
	tcchar m_strParm2[GLSL_STRUCT_NAME_LEN];
};

class T_DLL_EXPORT CLight : public CComponentBase
{
private:
	ELightType m_eType;

private:
	void InitGLSLName(n32 a_nIdx);
	void InitShader(n32 a_nShaderProgramID);

protected:
	sGLSLLightStructName m_objName;
	virtual void BindShader(n32 a_nShaderProgramID) T_PURE;

	friend class CLightManager;

public:
	tbool m_bEnable;
	glm::vec4 m_vDiffuseColor;
	glm::vec4 m_vSpecularColor;
	f32 m_fSpecularPower;

public: 
	CLight(ELightType a_eType);
	virtual ~CLight();

	ELightType GetLightType() { return this->m_eType; }
	virtual void Init() override;
};

class T_DLL_EXPORT CDirectionLight : public CLight
{
public:
	glm::vec3 m_vDirection;

public:
	CDirectionLight() : CLight(E_LIGHT_TYPE_DIRECTION)
	{
		this->m_vDirection = glm::normalize(glm::vec3(1.0f, -0.5f, 1.0f));
	}
	~CDirectionLight() {}
	virtual void BindShader(n32 a_nShaderProgramID);
};

class T_DLL_EXPORT CPointLight : public CLight
{
public:
	f32 m_fConstant;
	f32 m_fLinear;
	f32 m_fQuadratic;
	f32 m_fDistanceCutOff;

public:
	CPointLight() : CLight(E_LIGHT_TYPE_POINT)
	{
		this->m_fConstant = 0.0f;
		this->m_fLinear = 0.1f;
		this->m_fQuadratic = 0.00001f;
		this->m_fDistanceCutOff = 100.0f;
	}
	~CPointLight() {}
	virtual void BindShader(n32 a_nShaderProgramID);
};

class T_DLL_EXPORT CSpotLight : public CLight
{
public:
	glm::vec3 m_vDirection;
	f32 m_fConstant;
	f32 m_fLinear;
	f32 m_fQuadratic;
	f32 m_fDistanceCutOff;
	f32 m_fInnerAngle;
	f32 m_fOuterAngle;
	f32 m_fTBD;

public:
	CSpotLight() : CLight(E_LIGHT_TYPE_SPOT)
	{
		this->m_vDirection = glm::normalize(glm::vec3(1.0f, -0.5f, 1.0f));
		this->m_fConstant = 0.0f;
		this->m_fLinear = 0.1f;
		this->m_fQuadratic = 0.00001f;
		this->m_fDistanceCutOff = 100.0f;
		this->m_fInnerAngle = 0.0f;
		this->m_fOuterAngle = 0.0f;
		this->m_fTBD = 0.0f;
	}
	~CSpotLight() {}
	virtual void BindShader(n32 a_nShaderProgramID);
};

