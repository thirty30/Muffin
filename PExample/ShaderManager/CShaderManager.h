#pragma once

class CShaderManager : public CSingleton<CShaderManager>
{
private:
	hash_map<n32, CShaderProgram*> m_mapCustomID2Program;

public:
	CShaderManager() {}
	~CShaderManager() {}

	tbool Init();
	void Clear();
	CShaderProgram* FindShaderProgramByCustomID(n32 a_nCustomID);
};

