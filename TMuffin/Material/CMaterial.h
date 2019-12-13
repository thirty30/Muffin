#pragma once

class T_DLL_EXPORT CMaterialParam
{
public:
	EMaterialParamVariableType m_eType;
	tstring m_strName;
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
	hash_map<n32, CMaterialParam*> m_mapKey2Param;

public:
	CMaterial();
	~CMaterial();

	tbool Init(tstring a_strFileName);
	CMaterialParam* FindMaterialParam(n32 a_nID);
	virtual T_INLINE void RenderMaterial();
	T_INLINE n32 GetShaderID() { return this->m_pShaderProgram.GetShaderID(); }

	template<typename T>
	void SetParam(n32 a_nID, T a_v1, T a_v2, T a_v3, T a_v4);
};

template<typename T>
void CMaterial::SetParam(n32 a_nID, T a_v1, T a_v2, T a_v3, T a_v4)
{
	CMaterialParam* pParam = this->FindMaterialParam(a_nID);
	switch (pParam->m_eType)
	{
	case E_MPVT_INT:
		pParam->m_nData[0] = a_v1;
		break;
	case E_MPVT_INT_VEC2:
		pParam->m_nData[0] = a_v1;
		pParam->m_nData[1] = a_v2;
		break;
	case E_MPVT_INT_VEC3:
		pParam->m_nData[0] = a_v1;
		pParam->m_nData[1] = a_v2;
		pParam->m_nData[2] = a_v3;
		break;
	case E_MPVT_INT_VEC4:
		pParam->m_nData[0] = a_v1;
		pParam->m_nData[1] = a_v2;
		pParam->m_nData[2] = a_v3;
		pParam->m_nData[3] = a_v4;
		break;
	case E_MPVT_FLOAT:
		pParam->m_fData[0] = a_v1;
		break;
	case E_MPVT_FLOAT_VEC2:
		pParam->m_fData[0] = a_v1;
		pParam->m_fData[1] = a_v2;
		break;
	case E_MPVT_FLOAT_VEC3:
		pParam->m_fData[0] = a_v1;
		pParam->m_fData[1] = a_v2;
		pParam->m_fData[2] = a_v3;
		break;
	case E_MPVT_FLOAT_VEC4:
		pParam->m_fData[0] = a_v1;
		pParam->m_fData[1] = a_v2;
		pParam->m_fData[2] = a_v3;
		pParam->m_fData[3] = a_v4;
		break;
	default:
		break;
	}
}
