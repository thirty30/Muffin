#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"

class T_DLL_EXPORT CShader
{
private:
	n32 m_nShaderID;
	EShaderType m_eShaderType;

public:
	CShader();
	~CShader();

	tbool InitShader(EShaderType a_eShaderTyep, tstring a_strFileName);
	n32 GetShaderID() { return this->m_nShaderID; }
};

class T_DLL_EXPORT CShaderProgram
{
private:
	n32 m_nShaderID;
	CShader m_pVertexShader;
	CShader m_pFragmentShader;

public:
	CShaderProgram();
	~CShaderProgram();

	tbool Init(const tcchar* a_strVertexShaderFile, const tcchar* a_strFragmentShaderFile);
	T_INLINE n32 GetShaderID() { return this->m_nShaderID; }
};

