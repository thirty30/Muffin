#include "stdafx.h"
#include <rapidjson/document.h>

CSceneBase::CSceneBase(n32 a_nSceneID) :
	m_nSceneID(a_nSceneID),
	m_GUIDMaker(1)
{
	this->m_strSceneName = "";
	this->m_mapID2GameObj.clear();
}

CSceneBase::~CSceneBase()
{
	for (auto iter : this->m_mapID2GameObj)
	{
		//delete iter.second;
	}
	this->m_mapID2GameObj.clear();
}

T_INLINE u64 CSceneBase::CreateGUID()
{
	return this->m_GUIDMaker.GenerateGUID(0);
}

T_INLINE void CSceneBase::AddGameObjet(CGameObject* a_pGameObject)
{
	u64 nGUID = a_pGameObject->GetGameObjectID();
	this->m_mapID2GameObj[nGUID] = a_pGameObject;
}

tbool CSceneBase::LoadSceneFile(const tcchar* a_strFileName)
{
#define JSON_TEXT_LENGTH 120400

	tcchar* pJsonText = new char[JSON_TEXT_LENGTH];
	TMemzero(pJsonText, JSON_TEXT_LENGTH);
	ifstream jsonFile(a_strFileName);
	if (jsonFile.is_open() == false)
	{
		cout << "open scene file error" << endl;
		return false;
	}
	jsonFile.read(pJsonText, JSON_TEXT_LENGTH);

	rapidjson::Document doc;
	doc.Parse(pJsonText);

#undef JSON_TEXT_LENGTH
	delete[]pJsonText;

	for (rapidjson::Value::ConstMemberIterator iterRoot = doc.MemberBegin(); iterRoot != doc.MemberEnd(); ++iterRoot)
	{
		tstring strKey = iterRoot->name.GetString();
		if (strKey == "SceneName")
		{
			this->m_strSceneName = strKey;
			continue;
		}
		if (strKey == "GameObject")
		{
			if (this->LoadSceneGameObject(iterRoot->value.GetObjectA()) == false)
			{
				return false;
			}
		}
	}
	return true;
}

tbool CSceneBase::LoadSceneGameObject(const rapidjson::Value::ConstObject& a_rNode)
{
	CGameObject* pObj = new CGameObject();

	//Transform
	{
		rapidjson::Value::ConstValueIterator iter = NULL;
		const rapidjson::Value& rTransform = a_rNode.FindMember("Transform")->value;
		if (rTransform.IsObject() == false)
		{
			return false;
		}
		CTransform& rTrans = pObj->GetTransform();
		const rapidjson::Value& rPosition = rTransform.FindMember("Position")->value;
		iter = rPosition.GetArray().Begin();
		rTrans.m_vPosition.x = (iter + 0)->GetFloat();
		rTrans.m_vPosition.y = (iter + 1)->GetFloat();
		rTrans.m_vPosition.z = (iter + 2)->GetFloat();

		const rapidjson::Value& rRotation = rTransform.FindMember("Rotation")->value;
		iter = rRotation.GetArray().Begin();
		glm::vec3 vAngle;
		vAngle.x = (iter + 0)->GetFloat();
		vAngle.y = (iter + 1)->GetFloat();
		vAngle.z = (iter + 2)->GetFloat();
		rTrans.SetRotation(vAngle);

		const rapidjson::Value& rScale = rTransform.FindMember("Scale")->value;
		iter = rScale.GetArray().Begin();
		rTrans.m_vScale.x = (iter + 0)->GetFloat();
		rTrans.m_vScale.y = (iter + 1)->GetFloat();
		rTrans.m_vScale.z = (iter + 2)->GetFloat();
	}

	//Components
	{
		const rapidjson::Value& rComponents = a_rNode.FindMember("Components")->value;
		if (rComponents.IsObject() == false)
		{
			return false;
		}
		rapidjson::Value::ConstMemberIterator iter = rComponents.MemberBegin();
		for (; iter != rComponents.MemberEnd(); ++iter)
		{
			tstring strKey = iter->name.GetString();
			const rapidjson::Value::ConstObject& rValue = iter->value.GetObjectA();
			CComponentBase* pCom = NULL;
			pCom = CreateComponent(pObj, strKey);
			if (pCom == NULL)
			{
				pCom = CreateLogicComponent(pObj, strKey);
			}
			if (pCom == NULL)
			{
				continue;
			}

			rapidjson::Value::ConstMemberIterator iterProperty = rValue.MemberBegin();
			for (; iterProperty != rValue.MemberEnd(); ++iterProperty)
			{
				if (iterProperty->value.IsString() == true)
				{
					pCom->SetProperty(iterProperty->name.GetString(), tstring(iterProperty->value.GetString()));
				}
				else if(iterProperty->value.IsInt() == true)
				{
					pCom->SetProperty(iterProperty->name.GetString(), iterProperty->value.GetInt());
				}
				else if (iterProperty->value.IsFloat() == true)
				{
					pCom->SetProperty(iterProperty->name.GetString(), iterProperty->value.GetFloat());
				}
				else if (iterProperty->value.IsBool() == true)
				{
					pCom->SetProperty(iterProperty->name.GetString(), iterProperty->value.GetBool());
				}
				else if (iterProperty->value.IsArray() == true)
				{
					n32 nLen = iterProperty->value.GetArray().Size();
					if (nLen == 2)
					{
						glm::vec2 v;
						v.x = iterProperty->value.GetArray().Begin()->GetFloat();
						v.y = (iterProperty->value.GetArray().Begin() + 1)->GetFloat();
						pCom->SetProperty(iterProperty->name.GetString(), v);
					}
					else if (nLen == 3)
					{
						glm::vec3 v;
						v.x = iterProperty->value.GetArray().Begin()->GetFloat();
						v.y = (iterProperty->value.GetArray().Begin() + 1)->GetFloat();
						v.z = (iterProperty->value.GetArray().Begin() + 2)->GetFloat();
						pCom->SetProperty(iterProperty->name.GetString(), v);
					}
					else if (nLen == 4)
					{
						glm::vec4 v;
						v.x = iterProperty->value.GetArray().Begin()->GetFloat();
						v.y = (iterProperty->value.GetArray().Begin() + 1)->GetFloat();
						v.z = (iterProperty->value.GetArray().Begin() + 2)->GetFloat();
						v.w = (iterProperty->value.GetArray().Begin() + 3)->GetFloat();
						pCom->SetProperty(iterProperty->name.GetString(), v);
					}
				}
			}
		}
	}

	this->AddGameObjet(pObj);

	return true;
}
