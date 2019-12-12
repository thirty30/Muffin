#include "pch.h"

CMaterial::CMaterial()
{
	this->m_mapKey2Param.clear();
}

CMaterial::~CMaterial()
{
	hash_map<string, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.begin();
	for (; iter != this->m_mapKey2Param.end(); iter++)
	{
		delete iter->second;
	}
	this->m_mapKey2Param.clear();
}

tbool CMaterial::Init(tstring a_strFileName)
{
#define JSON_TEXT_LENGTH 1204*10

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

	this->m_strMaterialName = doc["MaterialName"].GetString();
	tstring strVertexShaderFile = doc["VertexShader"].GetString();
	tstring strFragmentShaderFile = doc["FragmentShader"].GetString();
	if (this->m_pShaderProgram.Init(strVertexShaderFile.c_str(), strFragmentShaderFile.c_str()) == false)
	{
		return false;
	}

	const rapidjson::Value& materialData = doc["MaterialData"].GetArray();
	n32 aa = 0;
	for (rapidjson::Value::ConstValueIterator iter = materialData.Begin(); iter != materialData.End(); ++iter)
	{
		const rapidjson::Value::ConstObject& tempObj = iter->GetObjectW();
		const rapidjson::Value& rName = tempObj.FindMember("Name")->value;
		const rapidjson::Value& rTag = tempObj.FindMember("Tag")->value;
		const rapidjson::Value& rValue = tempObj.FindMember("Value")->value;

		if (this->FindMaterialParam(rName.GetString()) != NULL)
		{
			return false;
		}

#pragma region AnalysisParams
		CMaterialParam* pParam = new CMaterialParam();
		if (TStrcmp(rTag.GetString(), "Texture") == 0)
		{
			pParam->m_eType = E_MPVT_TEXTURE;
			pParam->m_pTexture = new CTexture();
			if (pParam->m_pTexture->LoadTexture(rValue.GetString()) == false)
			{
				return false;
			}
		}
		else if (TStrcmp(rTag.GetString(), "Int") == 0)
		{
			if (rValue.IsInt() == false) { return false; }
			pParam->m_eType = E_MPVT_INT;
			pParam->m_nData[0] = rValue.GetInt();
		}
		else if (TStrcmp(rTag.GetString(), "IntVec2") == 0)
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 2) { return false; }
			pParam->m_eType = E_MPVT_INT_VEC2;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_nData[0] = (tIter + 0)->GetInt();
			pParam->m_nData[1] = (tIter + 1)->GetInt();
		}
		else if (TStrcmp(rTag.GetString(), "IntVec3") == 0)
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 3) { return false; }
			pParam->m_eType = E_MPVT_INT_VEC3;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_nData[0] = (tIter + 0)->GetInt();
			pParam->m_nData[1] = (tIter + 1)->GetInt();
			pParam->m_nData[2] = (tIter + 2)->GetInt();
		}
		else if (TStrcmp(rTag.GetString(), "IntVec4") == 0)
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
		else if (TStrcmp(rTag.GetString(), "Float") == 0)
		{
			if (rValue.IsFloat() == false) { return false; }
			pParam->m_eType = E_MPVT_FLOAT;
			pParam->m_fData[0] = rValue.GetFloat();
		}
		else if (TStrcmp(rTag.GetString(), "FloatVec2") == 0)
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 2) { return false; }
			pParam->m_eType = E_MPVT_FLOAT_VEC2;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_fData[0] = (tIter + 0)->GetFloat();
			pParam->m_fData[1] = (tIter + 1)->GetFloat();
		}
		else if (TStrcmp(rTag.GetString(), "FloatVec3") == 0)
		{
			if (rValue.IsArray() == false) { return false; }
			if (rValue.GetArray().Size() != 3) { return false; }
			pParam->m_eType = E_MPVT_FLOAT_VEC3;
			rapidjson::Value::ConstValueIterator tIter = rValue.Begin();
			pParam->m_fData[0] = (tIter + 0)->GetFloat();
			pParam->m_fData[1] = (tIter + 1)->GetFloat();
			pParam->m_fData[2] = (tIter + 2)->GetFloat();
		}
		else if (TStrcmp(rTag.GetString(), "FloatVec4") == 0)
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
		
		pParam->m_nULID = glGetUniformLocation(this->m_pShaderProgram.GetShaderID(), rName.GetString());
		this->m_mapKey2Param[rName.GetString()] = pParam;

#pragma endregion regionName

		aa++;

	}

#undef JSON_TEXT_LENGTH
	delete[]pJsonText;
	return true;
}

CMaterialParam* CMaterial::FindMaterialParam(tstring a_strKey)
{
	hash_map<tstring, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.find(a_strKey);
	if (iter != this->m_mapKey2Param.end())
	{
		return iter->second;
	}
	return NULL;
}

T_INLINE void CMaterial::RenderMaterial()
{
	n32 nIdx = 0;
	hash_map<string, CMaterialParam*>::const_iterator iter = this->m_mapKey2Param.begin();
	for (; iter != this->m_mapKey2Param.end(); iter++)
	{
		CMaterialParam* pParam = iter->second;
		if (pParam->m_eType == E_MPVT_TEXTURE)
		{
			glActiveTexture(GL_TEXTURE0 + nIdx);
			glBindTexture(GL_TEXTURE_2D, pParam->m_pTexture->GetTextureID());
			glUniform1i(pParam->m_nULID, nIdx);
			nIdx++;
		}
	}
}
