#include "pch.h"

tbool CShader::GenerateShaderID()
{
	switch (this->m_eShaderType)
	{
	case E_SHADER_TYPE_VERTEX:
	{
		this->m_nOpenGLID = glCreateShader(GL_VERTEX_SHADER);
	}
	break;
	case E_SHADER_TYPE_FRAGMENT:
	{
		this->m_nOpenGLID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	break;
	default:
	{
		return false;
	}
	break;
	}
	return true;
}

tbool CShader::LoadShaderText()
{
	ifstream objShaderFile(this->m_strFileName);
	if (objShaderFile.is_open() == false)
	{
		return false;
	}
	this->m_strShaderText = new tcchar[SHADER_TEXT_LEN];
	TMemzero(this->m_strShaderText, SHADER_TEXT_LEN);
	objShaderFile.read(this->m_strShaderText, SHADER_TEXT_LEN);
	objShaderFile.close();
	return true;
}

tbool CShader::CompileShader()
{
	if (this->GenerateShaderID() == false)
	{
		return false;
	}
	GLint nShaderTextLen = strlen(this->m_strShaderText);
	glShaderSource(this->m_nOpenGLID, 1, &this->m_strShaderText, &nShaderTextLen);
	glCompileShader(this->m_nOpenGLID);

	GLint nIsCompiled = 0;
	glGetShaderiv(this->m_nOpenGLID, GL_COMPILE_STATUS, &nIsCompiled);
	if (nIsCompiled == GL_FALSE)
	{
		GLint nLogLength = 0;
		glGetShaderiv(this->m_nOpenGLID, GL_INFO_LOG_LENGTH, &nLogLength);
		tcchar* pLogText = new tcchar[nLogLength];
		glGetShaderInfoLog(this->m_nOpenGLID, nLogLength, &nLogLength, pLogText);
		cout << "Compiled Shader Error: " << this->m_strFileName << pLogText << endl;
		delete[] pLogText;
		return false;
	}

	return true;
}

CShader::CShader(EShaderType a_eShaderTyep, tstring a_strFileName)
{
	this->m_nOpenGLID = 0;
	this->m_eShaderType = a_eShaderTyep;
	this->m_strFileName = a_strFileName;
	this->m_strShaderText = NULL;
}

CShader::~CShader()
{
	if (this->m_strShaderText != NULL)
	{
		delete this->m_strShaderText;
	}
}

tstring CShader::GetShaderType()
{
	switch (this->m_eShaderType)
	{
	case E_SHADER_TYPE_VERTEX:
	{
		return "Vertex Shader";
	}
	break;
	case E_SHADER_TYPE_FRAGMENT:
	{
		return "Fragment Shader";
	}
	break;
	default:
	{
		return "Unknown Shader";
	}
	break;
	}
}

tbool CShader::InitShader()
{
	if (this->LoadShaderText() == false)
	{
		return false;
	}
	if (this->CompileShader() == false)
	{
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

tbool CreateShaderProgram(CShader* a_pVertexShader, CShader* a_pFragmentShader, CShaderProgram* o_pShaderProgram)
{
	if (a_pVertexShader == NULL || a_pFragmentShader == NULL || o_pShaderProgram == NULL)
	{
		return false;
	}
	n32 nProgramID = glCreateProgram();
	glAttachShader(nProgramID, a_pVertexShader->m_nOpenGLID);
	glAttachShader(nProgramID, a_pFragmentShader->m_nOpenGLID);
	glLinkProgram(nProgramID);

	//check link error
	GLint nIsLinked = 0;
	glGetProgramiv(nProgramID, GL_LINK_STATUS, &nIsLinked);
	if (nIsLinked == GL_FALSE)
	{
		GLint nLogLength = 0;
		glGetProgramiv(nProgramID, GL_INFO_LOG_LENGTH, &nLogLength);
		tcchar* pLogText = new tcchar[nLogLength];
		TMemzero(pLogText, nLogLength);
		glGetProgramInfoLog(nProgramID, nLogLength, &nLogLength, pLogText);
		cout << "Link Shader Error: " << pLogText << endl;
		delete[] pLogText;
		return false;
	}

	o_pShaderProgram->m_nOpenGLID = nProgramID;
	o_pShaderProgram->m_pVertexShader = a_pVertexShader;
	o_pShaderProgram->m_pFragmentShader = a_pFragmentShader;

	return true;
}
