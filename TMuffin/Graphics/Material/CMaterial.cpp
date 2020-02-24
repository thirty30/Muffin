#include "CMaterial.h"
#include "Graphics/Texture/CTexture.h"
#include "GameObject/CGameObject.h"
#include "Graphics/FBO/CFBOComponent.h"

CMaterial::CMaterial()
{
	this->m_mapKey2Param.clear();
}

CMaterial::~CMaterial()
{
	hash_map<n32, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.begin();
	for (; iter != this->m_mapKey2Param.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapKey2Param.clear();
}

tbool CMaterial::Init(tstring a_strFileName)
{
#define JSON_TEXT_LENGTH 12040

	tcchar* pJsonText = new tcchar[JSON_TEXT_LENGTH];
	TMemzero(pJsonText, JSON_TEXT_LENGTH);
	ifstream jsonFile(a_strFileName);
	if (jsonFile.is_open() == false)
	{
		return false;
	}
	jsonFile.read(pJsonText, JSON_TEXT_LENGTH);

	rapidjson::Document doc;
	doc.Parse(pJsonText);

	// Init shader
	this->m_strMaterialName = doc["MaterialName"].GetString();
	tstring strVertexShaderFile = doc["VertexShader"].GetString();
	tstring strFragmentShaderFile = doc["FragmentShader"].GetString();
	if (this->m_pShaderProgram.Init(strVertexShaderFile.c_str(), strFragmentShaderFile.c_str()) == false)
	{
		return false;
	}

	// Init params
	const rapidjson::Value& materialData = doc["MaterialData"].GetArray();
	for (rapidjson::Value::ConstValueIterator iter = materialData.Begin(); iter != materialData.End(); ++iter)
	{
		const rapidjson::Value::ConstObject& tempObj = iter->GetObjectW();
		const rapidjson::Value& rID = tempObj.FindMember("ID")->value;
		const rapidjson::Value& rName = tempObj.FindMember("Name")->value;
		const rapidjson::Value& rTag = tempObj.FindMember("Tag")->value;
		const rapidjson::Value& rValue = tempObj.FindMember("Value")->value;

		if (rID.IsNull() || rID.IsInt() == false)
		{
			return false;
		}
		n32 nID = rID.GetInt();
		if (this->FindMaterialParam(nID) != NULL)
		{
			return false;
		}

#pragma region AnalysisParams
		CMaterialParam* pParam = new CMaterialParam();
		pParam->m_strName = rName.GetString();
		pParam->m_nULID = glGetUniformLocation(this->m_pShaderProgram.GetShaderID(), rName.GetString());

		string strTag = rTag.GetString();
		if (strTag == "Texture")
		{
			pParam->m_eType = E_MPVT_TEXTURE;
			pParam->m_pTexture = new CTexture();
			if (pParam->m_pTexture->LoadTexture(rValue.GetString()) == false)
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
		this->m_mapKey2Param[nID] = pParam;

#pragma endregion regionName

	}

#undef JSON_TEXT_LENGTH
	delete[]pJsonText;
	return true;
}

CMaterialParam* CMaterial::FindMaterialParam(n32 a_nID)
{
	hash_map<n32, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.find(a_nID);
	if (iter != this->m_mapKey2Param.end())
	{
		return iter->second;
	}
	return NULL;
}

T_INLINE void CMaterial::RenderMaterial(CGameObject* a_pGameObject, GLuint a_nSkyBoxID)
{
	n32 nTextureIdx = 0;
	hash_map<n32, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.begin();
	for (; iter != this->m_mapKey2Param.end(); iter++)
	{
		CMaterialParam* pParam = iter->second;
		if (pParam->m_eType == E_MPVT_TEXTURE)
		{

		}
		switch (pParam->m_eType)
		{
		case E_MPVT_TEXTURE:
			glActiveTexture(GL_TEXTURE0 + nTextureIdx);
			glBindTexture(GL_TEXTURE_2D, pParam->m_pTexture->GetTextureID());
			glUniform1i(pParam->m_nULID, nTextureIdx);
			nTextureIdx++;
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
		default:
			break;
		}
	}
}
