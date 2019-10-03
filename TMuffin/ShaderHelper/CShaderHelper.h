#pragma once

class T_DLL_EXPORT CShader
{
private:
#define SHADER_TEXT_LEN 1024*64
	tstring m_strFileName;
	tcchar* m_strShaderText;

public:
	n32 m_nOpenGLID;	//from OpenGL
	EShaderType m_eShaderType;

private:
	tbool GenerateShaderID();
	tbool LoadShaderText();
	tbool CompileShader();

public:
	CShader(EShaderType a_eShaderTyep, tstring a_strFileName);
	~CShader();

	tstring GetShaderType();
	tbool InitShader();
};

class T_DLL_EXPORT CShaderProgram
{
public:
	n32 m_nOpenGLID;
	CShader* m_pVertexShader;
	CShader* m_pFragmentShader;

	CShaderProgram()
	{
		this->m_nOpenGLID = 0;
		this->m_pVertexShader = NULL;
		this->m_pFragmentShader = NULL;
	}
};

T_DLL_EXPORT tbool CreateShaderProgram(CShader* a_pVertexShader, CShader* a_pFragmentShader, CShaderProgram* o_pShaderProgram);


