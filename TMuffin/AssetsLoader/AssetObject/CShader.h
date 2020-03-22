#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"

class T_DLL_EXPORT CShader
{
private:
	EShaderType m_eShaderType;
	GLint m_nShaderID;
	tstring m_strFileName;
	n32 m_nShaderTextLen;
	tcchar* m_strShaderText;

public:
	CShader(EShaderType a_eShaderTyep);
	~CShader();

	tbool LoadShaderToMemory(tstring a_strFileName);
	tbool InitShader();
	T_INLINE n32 GetShaderID() { return this->m_nShaderID; }
};

class T_DLL_EXPORT CShaderProgram
{
private:
	n32 m_nShaderID;
	CShader m_VertexShader;
	CShader m_FragmentShader;

public:
	CShaderProgram();
	~CShaderProgram();

	tbool InitShaderProgram();
	T_INLINE n32 GetShaderID() { return this->m_nShaderID; }
	T_INLINE CShader* GetShader(EShaderType a_eShaderTyep);
};

