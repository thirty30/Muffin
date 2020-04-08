#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"
#include "CShader.h"
#include "CAssetObject.h"

class CTexture;
class CMaterialParam
{
public:
	tstring m_strName;
	EMaterialParamVariableType m_eType;
	GLint m_nULID;

	CTexture* m_pTexture;
	n32 m_nData[4];
	f32 m_fData[4];
	n32 m_nInc;
	f32 m_fInc;

	CMaterialParam();
	~CMaterialParam();
};

class CGameObject;
class T_DLL_EXPORT CMaterial : public CAssetObject
{
private:
	CShaderProgram m_ShaderProgram;
	vector<CMaterialParam*> m_vecParams;

public:
	CMaterial();
	~CMaterial();

	T_INLINE void RenderMaterial(CGameObject* a_pGameObject, GLuint a_nSkyBoxID);
	T_INLINE n32 GetShaderID() { return this->m_ShaderProgram.GetShaderID(); }

	CMaterialParam* CreateAMaterialParam();
	template<typename T>
	void SetParam(n32 a_nID, T a_v1, T a_v2, T a_v3, T a_v4);

protected:
	virtual tbool LoadToMemory(const tcchar* a_strFileName) override;
	virtual tbool InitAfterLoad() override;

};

template<typename T>
void CMaterial::SetParam(n32 a_nIDX, T a_v1, T a_v2, T a_v3, T a_v4)
{
	if (a_nIDX < 0 || a_nIDX >= this->m_vecParams.size())
	{
		return;
	}
	CMaterialParam* pParam = this->m_vecParams[a_nIDX];
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

