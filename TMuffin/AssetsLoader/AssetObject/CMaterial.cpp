#include "CMaterial.h"
#include "GameObject/CGameObject.h"
#include "Graphics/FBO/CFBOComponent.h"
#include "CTexture.h"
#include "Engine/Engine.h"

CMaterialParam::CMaterialParam()
{
	this->m_eType = E_MPVT_UNKNOWN;
	this->m_pTexture = NULL;
	TMemzero(this->m_nData, 0);
	TMemzero(this->m_fData, 0);
	this->m_nULID = -1;
	this->m_nInc = 0;
	this->m_fInc = 0.0f;
}

CMaterialParam::~CMaterialParam()
{
	if (this->m_pTexture != NULL)
	{
		delete this->m_pTexture;
	}
	this->m_pTexture = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////



CMaterial::CMaterial() : CAssetObject(EAT_MATERIAL)
{
	this->m_vecParams.clear();
}

CMaterial::~CMaterial()
{
	for (n32 i = 0; i < this->m_vecParams.size(); i++)
	{
		delete this->m_vecParams[i];
	}
	this->m_vecParams.clear();
}

tbool CMaterial::LoadToMemory(const tcchar* a_strFileName)
{
#define JSON_TEXT_LENGTH 12040
	tcchar* pJsonText = new tcchar[JSON_TEXT_LENGTH];
	TMemzero(pJsonText, JSON_TEXT_LENGTH);
	ifstream jsonFile(a_strFileName, ifstream::in | ios::binary);
	if (jsonFile.is_open() == false)
	{
		return false;
	}
	jsonFile.read(pJsonText, JSON_TEXT_LENGTH);

	rapidjson::Document doc;
	doc.Parse(pJsonText);

#undef JSON_TEXT_LENGTH
	delete[]pJsonText;

	// Init shader
	tstring strVertexShaderFile = doc["VertexShader"].GetString();
	if (this->m_ShaderProgram.GetShader(E_SHADER_TYPE_VERTEX)->LoadShaderToMemory(strVertexShaderFile) == false)
	{
		return false;
	}

	tstring strFragmentShaderFile = doc["FragmentShader"].GetString();
	if (this->m_ShaderProgram.GetShader(E_SHADER_TYPE_FRAGMENT)->LoadShaderToMemory(strFragmentShaderFile) == false)
	{
		return false;
	}

	// Init params
	const rapidjson::Value& materialData = doc["MaterialData"].GetArray();
	for (rapidjson::Value::ConstValueIterator iter = materialData.Begin(); iter != materialData.End(); ++iter)
	{
		const rapidjson::Value::ConstObject& tempObj = iter->GetObjectW();
		const rapidjson::Value& rName = tempObj.FindMember("Name")->value;
		const rapidjson::Value& rTag = tempObj.FindMember("Tag")->value;
		const rapidjson::Value& rValue = tempObj.FindMember("Value")->value;

#pragma region AnalysisParams
		CMaterialParam* pParam = this->CreateAMaterialParam();
		pParam->m_strName = rName.GetString();
		string strTag = rTag.GetString();
		if (strTag == "Texture")
		{
			pParam->m_eType = E_MPVT_TEXTURE;
			pParam->m_pTexture = new CTexture();
			if (pParam->m_pTexture->LoadToMemory(rValue.GetString()) == false)
			{
				return false;
			}
		}
		else if (strTag == "FBOTexture")
		{
			pParam->m_eType = E_MPVT_FBO_TEXTURE;
		}
		else if (strTag == "SkyBoxCubeMap")
		{
			pParam->m_eType = E_MPVT_FBO_SKYBOXCUBEMAP;
		}
		else if (strTag == "Int")
		{
			if (rValue.IsInt() == false) { return false; }
			pParam->m_eType = E_MPVT_INT;
			pParam->m_nData[0] = rValue.GetInt();
		}
		else if (strTag == "IntVec2")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 2) { return false; }
			pParam->m_eType = E_MPVT_INT_VEC2;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_nData[0] = (tIter + 0)->GetInt();
			pParam->m_nData[1] = (tIter + 1)->GetInt();
		}
		else if (strTag == "IntVec3")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 3) { return false; }
			pParam->m_eType = E_MPVT_INT_VEC3;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_nData[0] = (tIter + 0)->GetInt();
			pParam->m_nData[1] = (tIter + 1)->GetInt();
			pParam->m_nData[2] = (tIter + 2)->GetInt();
		}
		else if (strTag == "IntVec4")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 4) { return false; }
			pParam->m_eType = E_MPVT_INT_VEC4;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_nData[0] = (tIter + 0)->GetInt();
			pParam->m_nData[1] = (tIter + 1)->GetInt();
			pParam->m_nData[2] = (tIter + 2)->GetInt();
			pParam->m_nData[3] = (tIter + 3)->GetInt();
		}
		else if (strTag == "Float")
		{
			if (rValue.IsFloat() == false) { return false; }
			pParam->m_eType = E_MPVT_FLOAT;
			pParam->m_fData[0] = rValue.GetFloat();
		}
		else if (strTag == "FloatVec2")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 2) { return false; }
			pParam->m_eType = E_MPVT_FLOAT_VEC2;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_fData[0] = (tIter + 0)->GetFloat();
			pParam->m_fData[1] = (tIter + 1)->GetFloat();
		}
		else if (strTag == "FloatVec3")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 3) { return false; }
			pParam->m_eType = E_MPVT_FLOAT_VEC3;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_fData[0] = (tIter + 0)->GetFloat();
			pParam->m_fData[1] = (tIter + 1)->GetFloat();
			pParam->m_fData[2] = (tIter + 2)->GetFloat();
		}
		else if (strTag == "FloatVec4")
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 4) { return false; }
			pParam->m_eType = E_MPVT_FLOAT_VEC4;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_fData[0] = (tIter + 0)->GetFloat();
			pParam->m_fData[1] = (tIter + 1)->GetFloat();
			pParam->m_fData[2] = (tIter + 2)->GetFloat();
			pParam->m_fData[3] = (tIter + 3)->GetFloat();
		}
		else if (strTag == "AutoFloat")
		{
			if (rValue.IsFloat() == false) { return false; }
			pParam->m_eType = E_MPVT_AUTO_FLOAT;
			pParam->m_fData[0] = rValue.GetFloat();
		}
		else if (strTag == "AutoInt")
		{
			if (rValue.IsInt() == false) { return false; }
			pParam->m_eType = E_MPVT_AUTO_INT;
			pParam->m_nData[0] = rValue.GetInt();
		}
		else if (strTag == "AutoDeltaTime")
		{
			pParam->m_eType = E_MPVT_AUTO_DLETA_TIME;
		}
		else if (strTag == "FrameDeltaTime")
		{
			pParam->m_eType = E_MPVT_FRAME_DLETA_TIME;
		}
		else if (strTag == "GameNowTime")
		{
			pParam->m_eType = E_MPVT_GAME_NOW_TIME;
		}
#pragma endregion regionName

	}
	return true;
}

tbool CMaterial::InitAfterLoad()
{
	if (this->m_ShaderProgram.GetShader(E_SHADER_TYPE_VERTEX)->InitShader() == false)
	{
		return false;
	}

	if (this->m_ShaderProgram.GetShader(E_SHADER_TYPE_FRAGMENT)->InitShader() == false)
	{
		return false;
	}

	if (this->m_ShaderProgram.InitShaderProgram() == false)
	{
		return false;
	}

	for (n32 i = 0; i < this->m_vecParams.size(); i++)
	{
		CMaterialParam* pParam = this->m_vecParams[i];
		pParam->m_nULID = glGetUniformLocation(this->m_ShaderProgram.GetShaderID(), pParam->m_strName.c_str());
		switch (pParam->m_eType)
		{
		case E_MPVT_TEXTURE:
		{
			pParam->m_pTexture->InitAfterLoad();
		}
		break;
		}
	}
	return true;
}

T_INLINE void CMaterial::RenderMaterial(CGameObject* a_pGameObject, GLuint a_nSkyBoxID)
{
	n32 nTextureIdx = 0;
	for (n32 i = 0; i < this->m_vecParams.size(); i++)
	{
		CMaterialParam* pParam = this->m_vecParams[i];
		switch (pParam->m_eType)
		{
		case E_MPVT_TEXTURE:
		{
			glActiveTexture(GL_TEXTURE0 + nTextureIdx);
			glBindTexture(GL_TEXTURE_2D, pParam->m_pTexture->GetTextureID());
			glUniform1i(pParam->m_nULID, nTextureIdx);
			nTextureIdx++;
		}
		break;
		case E_MPVT_FBO_TEXTURE:
		{
			CFBOComponent* pFBOCom = static_cast<CFBOComponent*>(a_pGameObject->GetComponent<CFBOComponent>());
			glActiveTexture(GL_TEXTURE0 + nTextureIdx);
			glBindTexture(GL_TEXTURE_2D, pFBOCom->GetColorTextureID());
			glUniform1i(pParam->m_nULID, nTextureIdx);
			nTextureIdx++;
		}
		break;
		case E_MPVT_FBO_SKYBOXCUBEMAP:
		{
			glActiveTexture(GL_TEXTURE0 + nTextureIdx);
			glBindTexture(GL_TEXTURE_CUBE_MAP, a_nSkyBoxID);
			glUniform1i(pParam->m_nULID, nTextureIdx);
			nTextureIdx++;
		}
		break;
		case E_MPVT_INT:
			glUniform1i(pParam->m_nULID, pParam->m_nData[0]);
			break;
		case E_MPVT_INT_VEC2:
			glUniform2i(pParam->m_nULID, pParam->m_nData[0], pParam->m_nData[1]);
			break;
		case E_MPVT_INT_VEC3:
			glUniform3i(pParam->m_nULID, pParam->m_nData[0], pParam->m_nData[1], pParam->m_nData[2]);
			break;
		case E_MPVT_INT_VEC4:
			glUniform4i(pParam->m_nULID, pParam->m_nData[0], pParam->m_nData[1], pParam->m_nData[2], pParam->m_nData[3]);
			break;
		case E_MPVT_FLOAT:
			glUniform1f(pParam->m_nULID, pParam->m_fData[0]);
			break;
		case E_MPVT_FLOAT_VEC2:
			glUniform2f(pParam->m_nULID, pParam->m_fData[0], pParam->m_fData[1]);
			break;
		case E_MPVT_FLOAT_VEC3:
			glUniform3f(pParam->m_nULID, pParam->m_fData[0], pParam->m_fData[1], pParam->m_fData[2]);
			break;
		case E_MPVT_FLOAT_VEC4:
			glUniform4f(pParam->m_nULID, pParam->m_fData[0], pParam->m_fData[1], pParam->m_fData[2], pParam->m_fData[3]);
			break;
		case E_MPVT_AUTO_FLOAT:
		{
			glUniform1f(pParam->m_nULID, pParam->m_fInc);
			pParam->m_fInc += pParam->m_fData[0];
		}
		break;
		case E_MPVT_AUTO_INT:
		{
			glUniform1i(pParam->m_nULID, pParam->m_nInc);
			pParam->m_nInc += pParam->m_nData[0];
		}
		break;
		case E_MPVT_AUTO_DLETA_TIME:
		{
			pParam->m_fInc += MUFFIN.GetDeltaFrameTime();
			glUniform1f(pParam->m_nULID, pParam->m_fInc);
		}
		break;
		case E_MPVT_FRAME_DLETA_TIME:
			glUniform1f(pParam->m_nULID, MUFFIN.GetDeltaFrameTime());
			break;
		case E_MPVT_GAME_NOW_TIME:
			glUniform1f(pParam->m_nULID, (f32)MUFFIN.GetNowFrameTime());
			break;
		default:
			break;
		}
	}
}

CMaterialParam* CMaterial::CreateAMaterialParam()
{
	CMaterialParam* pNew = new CMaterialParam();
	this->m_vecParams.push_back(pNew);
	return pNew;
}
