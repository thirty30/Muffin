#include "pch.h"
CShader::CShader()
{
	this->m_nShaderID = 0;
	this->m_eShaderType = E_SHADER_TYPE_UNKNOWN;
}

CShader::~CShader()
{

}

tbool CShader::InitShader(EShaderType a_eShaderTyep, tstring a_strFileName)
{
	this->m_eShaderType = a_eShaderTyep;

	// load shader text
	ifstream objShaderFile(a_strFileName);
	if (objShaderFile.is_open() == false)
	{
		return false;
	}
	n32 SHADER_TEXT_LEN = 1024 * 64;
	tcchar* pShaderText = new tcchar[SHADER_TEXT_LEN];
	TMemzero(pShaderText, SHADER_TEXT_LEN);
	objShaderFile.read(pShaderText, SHADER_TEXT_LEN);
	objShaderFile.close();

	// compile shader
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
	GLint nShaderTextLen = strlen(pShaderText);
	glShaderSource(this->m_nShaderID, 1, &pShaderText, &nShaderTextLen);
	glCompileShader(this->m_nShaderID);

	GLint nIsCompiled = 0;
	glGetShaderiv(this->m_nShaderID, GL_COMPILE_STATUS, &nIsCompiled);
	if (nIsCompiled == GL_FALSE)
	{
		GLint nLogLength = 0;
		glGetShaderiv(this->m_nShaderID, GL_INFO_LOG_LENGTH, &nLogLength);
		tcchar* pLogText = new tcchar[nLogLength];
		glGetShaderInfoLog(this->m_nShaderID, nLogLength, &nLogLength, pLogText);
		cout << "Compiled Shader Error: " << a_strFileName << pLogText << endl;
		delete[] pLogText;
		return false;
	}
	delete[]pShaderText;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


CShaderProgram::CShaderProgram()
{
	this->m_nShaderID = -1;
}

CShaderProgram::~CShaderProgram()
{

}

tbool CShaderProgram::Init(const tcchar* a_strVertexShaderFile, const tcchar* a_strFragmentShaderFile)
{
	this->m_pVertexShader.InitShader(E_SHADER_TYPE_VERTEX, a_strVertexShaderFile);
	this->m_pFragmentShader.InitShader(E_SHADER_TYPE_FRAGMENT, a_strFragmentShaderFile);

	this->m_nShaderID = glCreateProgram();
	glAttachShader(this->m_nShaderID, this->m_pVertexShader.GetShaderID());
	glAttachShader(this->m_nShaderID, this->m_pFragmentShader.GetShaderID());
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
