#pragma once

class CMaterialParam
{
public:
	EMaterialParamVariableType m_eType;
	CTexture* m_pTexture;
	n32 m_nData[4];
	f32 m_fData[4];
	GLint m_nULID;

	CMaterialParam()
	{
		this->m_eType = E_MPVT_UNKNOWN;
		this->m_pTexture = NULL;
		TMemzero(this->m_nData, 0);
		TMemzero(this->m_fData, 0);
		this->m_nULID = -1;
	}
	~CMaterialParam() {}
};

class T_DLL_EXPORT CMaterial
{
private:
	string m_strMaterialName;
	CShaderProgram m_pShaderProgram;
	hash_map<tstring, CMaterialParam*> m_mapKey2Param;

public:
	CMaterial();
	~CMaterial();

	tbool Init(tstring a_strFileName);
	CMaterialParam* FindMaterialParam(tstring a_strKey);
	virtual T_INLINE void RenderMaterial();
	T_INLINE n32 GetShaderID() { return this->m_pShaderProgram.GetShaderID(); }
};
