#include "CShader.h"

CShader::CShader(EShaderType a_eShaderTyep)
{
	this->m_eShaderType = a_eShaderTyep;
	this->m_nShaderID = -1;
	this->m_nShaderTextLen = 0;
	this->m_strShaderText = NULL;
}

CShader::~CShader()
{
	this->m_eShaderType = E_SHADER_TYPE_UNKNOWN;
	this->m_nShaderID = -1;
	this->m_strFileName = "";
	this->m_nShaderTextLen = 0;
	if (this->m_strShaderText != NULL)
	{
		delete[] this->m_strShaderText;
	}
}

tbool CShader::LoadShaderToMemory(tstring a_strFileName)
{
	this->m_strFileName = a_strFileName;
	ifstream objShaderFile(a_strFileName);
	if (objShaderFile.is_open() == false)
	{
		return false;
	}
	objShaderFile.seekg(0, ios::end);
	this->m_nShaderTextLen = objShaderFile.tellg();
	objShaderFile.seekg(0);
	this->m_strShaderText = new tcchar[this->m_nShaderTextLen];
	TMemzero(this->m_strShaderText, this->m_nShaderTextLen);
	objShaderFile.read(this->m_strShaderText, this->m_nShaderTextLen);
	objShaderFile.close();
	return true;
}

tbool CShader::InitShader()
{
	// compile shader
	if (this->m_nShaderTextLen <= 0)
	{
		return false;
	}

	if (this->m_eShaderType == E_SHADER_TYPE_VERTEX)
	{
		this->m_nShaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (this->m_eShaderType == E_SHADER_TYPE_FRAGMENT)
	{
		this->m_nShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		return false;
	}
	glShaderSource(this->m_nShaderID, 1, &this->m_strShaderText, &this->m_nShaderTextLen);
	glCompileShader(this->m_nShaderID);

	GLint nIsCompiled = 0;
	glGetShaderiv(this->m_nShaderID, GL_COMPILE_STATUS, &nIsCompiled);
	if (nIsCompiled == GL_FALSE)
	{
		GLint nLogLength = 0;
		glGetShaderiv(this->m_nShaderID, GL_INFO_LOG_LENGTH, &nLogLength);
		tcchar* pLogText = new tcchar[nLogLength];
		glGetShaderInfoLog(this->m_nShaderID, nLogLength, &nLogLength, pLogText);
		cout << "Compiled Shader Error: " << this->m_strFileName << endl << pLogText << endl;
		delete[] pLogText;
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

CShaderProgram::CShaderProgram() :
	m_VertexShader(E_SHADER_TYPE_VERTEX),
	m_FragmentShader(E_SHADER_TYPE_FRAGMENT)
{
	this->m_nShaderID = -1;
}

CShaderProgram::~CShaderProgram()
{
}

tbool CShaderProgram::InitShaderProgram()
{
	if (this->m_VertexShader.InitShader() == false)
	{
		return false;
	}
	if (this->m_FragmentShader.InitShader() == false)
	{
		return false;
	}

	this->m_nShaderID = glCreateProgram();
	glAttachShader(this->m_nShaderID, this->m_VertexShader.GetShaderID());
	glAttachShader(this->m_nShaderID, this->m_FragmentShader.GetShaderID());
	glLinkProgram(this->m_nShaderID);

	//check link error
	GLint nIsLinked = 0;
	glGetProgramiv(this->m_nShaderID, GL_LINK_STATUS, &nIsLinked);
	if (nIsLinked == GL_FALSE)
	{
		GLint nLogLength = 0;
		glGetProgramiv(this->m_nShaderID, GL_INFO_LOG_LENGTH, &nLogLength);
		tcchar* pLogText = new tcchar[nLogLength];
		TMemzero(pLogText, nLogLength);
		glGetProgramInfoLog(this->m_nShaderID, nLogLength, &nLogLength, pLogText);
		cout << "Link Shader Error: " << pLogText << endl;
		delete[] pLogText;
		return false;
	}

	return true;
}

CShader* CShaderProgram::GetShader(EShaderType a_eShaderTyep)
{
	if (a_eShaderTyep == E_SHADER_TYPE_VERTEX)
	{
		return &this->m_VertexShader;
	}
	else if (a_eShaderTyep == E_SHADER_TYPE_FRAGMENT)
	{
		return &this->m_FragmentShader;
	}
	else
	{
		return NULL;
	}
}
