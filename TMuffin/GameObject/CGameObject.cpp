#include "pch.h"
#include "./CGameObject.h"

CGameObject::CGameObject()
{
	this->m_nMuffinGameObectGUID = MUFFIN.GetGUIDMaker()->GenerateGUID(E_GUID_TYPE_GAME_OBJECT);
	this->m_bEnable = true;
	this->m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_qRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_nLineTweenIDGen = 0;
	this->m_vecSerialLineTween.clear();
	this->m_vecParallelLineTween.clear();

	MUFFIN.GetGameObjectMgr()->AddObject(this);
}

CGameObject::~CGameObject()
{
	for (n32 i = 0; i < this->m_vecSerialLineTween.size(); i++)
	{
		delete this->m_vecSerialLineTween[i];
	}
	this->m_vecSerialLineTween.clear();

	for (n32 i = 0; i < this->m_vecParallelLineTween.size(); i++)
	{
		delete this->m_vecParallelLineTween[i];
	}
	this->m_vecParallelLineTween.clear();
}

void CGameObject::SetRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation = glm::quat(vAngle);
}

void CGameObject::SetRotation(glm::quat a_quat)
{
	this->m_qRotation = a_quat;
}

void CGameObject::UpdateRotation(glm::vec3 a_vEulerAngle)
{
	glm::vec3 vAngle;
	vAngle.x = glm::radians(a_vEulerAngle.x);
	vAngle.y = glm::radians(a_vEulerAngle.y);
	vAngle.z = glm::radians(a_vEulerAngle.z);

	this->m_qRotation *= glm::quat(vAngle);
}

void CGameObject::UpdateRotation(glm::quat a_quat)
{
	this->m_qRotation *= a_quat;
}

glm::vec3 CGameObject::GetEulerAngle()
{
	return glm::eulerAngles(this->m_qRotation);
}

CLineTween* CGameObject::CreateLineTween(ELineTweenType a_eType)
{
	CLineTween* pLineTween = NULL;
	switch (a_eType)
	{
	case E_LINETWEEN_TYPE_MOVE_TO:
		pLineTween = new CLineTweenMove(++this->m_nLineTweenIDGen, this);
		break;
	case E_LINETWEEN_TYPE_SCALE_TO:
		pLineTween = new CLineTweenScale(++this->m_nLineTweenIDGen, this);
		break;
	case E_LINETWEEN_TYPE_ROTATE_TO:
		pLineTween = new CLineTweenRotation(++this->m_nLineTweenIDGen, this);
		break;
	case E_LINETWEEN_TYPE_CURVE:
		pLineTween = new CLineTweenCurve(++this->m_nLineTweenIDGen, this);
		break;
	case E_LINETWEEN_TYPE_FOLLOW:
		pLineTween = new CLineTweenFollow(++this->m_nLineTweenIDGen, this);
		break;
	default:
		break;
	}
	return pLineTween;
}

CLineTween* CGameObject::CreateSerialLineTween(ELineTweenType a_eType)
{
	CLineTween* pLineTween = this->CreateLineTween(a_eType);
	if (pLineTween != NULL)
	{
		this->m_vecSerialLineTween.push_back(pLineTween);
	}
	return pLineTween;
}

CLineTween* CGameObject::CreateParallelLineTween(ELineTweenType a_eType)
{
	CLineTween* pLineTween = this->CreateLineTween(a_eType);
	if (pLineTween != NULL)
	{
		this->m_vecParallelLineTween.push_back(pLineTween);
	}
	return pLineTween;
}

void CGameObject::Update()
{
	this->UpdateAnimation();
}

void CGameObject::UpdateAnimation()
{
	for (n32 i = 0; i < this->m_vecSerialLineTween.size(); i++)
	{
		CLineTween* pAnimation = this->m_vecSerialLineTween[i];
		if (pAnimation->IsDone() == false)
		{
			pAnimation->Update();
			break;
		}
	}

	for (n32 i = 0; i < this->m_vecParallelLineTween.size(); i++)
	{
		CLineTween* pAnimation = this->m_vecParallelLineTween[i];
		pAnimation->Update();
	}
}


