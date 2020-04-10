#include "CAudioManager.h"
#include "Engine/Engine.h"

CAudioManager::CAudioManager()
{
	this->m_pFmodSystem = NULL;
	this->m_mapAudio.clear();
}

CAudioManager::~CAudioManager()
{


}

tbool CAudioManager::Init()
{
	FMOD_RESULT res = FMOD_OK;
	res = FMOD::System_Create(&this->m_pFmodSystem);
	if (res != FMOD_OK)
	{
		return false;
	}
	res = this->m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	if (res != FMOD_OK)
	{
		return false;
	}
	return true;
}

void CAudioManager::Clear()
{
	if (this->m_pFmodSystem != NULL)
	{
		this->m_pFmodSystem->close();
		this->m_pFmodSystem->release();
	}

	for (auto iter : this->m_mapAudio)
	{
		CAudio* pAudio = iter.second;
		pAudio->Clear();
		delete pAudio;
	}
	this->m_mapAudio.clear();
}

void CAudioManager::LoadAudio(tstring a_strName, const tcchar* a_pFile)
{
	if (this->FindAudio(a_strName) != NULL)
	{
		return;
	}
	CAudio* pAudio = CAssetsLoader::Load<CAudio>(a_pFile);
	this->AddAudio(a_strName, pAudio);
}

void CAudioManager::LoadAudioASync(tstring a_strName, const tcchar* a_pFile)
{
	if (this->FindAudio(a_strName) != NULL)
	{
		return;
	}
	tcchar* strName = new tcchar[a_strName.length()];
	TMemcpy(strName, a_strName.length(), a_strName.c_str(), a_strName.length());
	CAssetsLoader::LoadASync<CAudio>(a_pFile, strName, LoadAudioCallBack);
}

CAudio* CAudioManager::FindAudio(tstring a_strName)
{
	auto iter = this->m_mapAudio.find(a_strName);
	if (iter == this->m_mapAudio.end())
	{
		return NULL;
	}
	return iter->second;
}

void CAudioManager::AddAudio(tstring a_strName, CAudio* a_pAudio)
{
	this->m_mapAudio[a_strName] = a_pAudio;
}

void CAudioManager::Play(tstring a_strName, tbool a_bIsLoop, f32 a_fVolume)
{
	CAudio* pAudio = this->FindAudio(a_strName);
	if (pAudio == NULL)
	{
		return;
	}

	if (a_bIsLoop == true)
	{
		pAudio->m_pSound->setLoopCount(-1);
	}
	
	if (pAudio->m_pChannel != NULL)
	{
		tbool bIsPlaying = false;
		pAudio->m_pChannel->isPlaying(&bIsPlaying);
		if (bIsPlaying == true)
		{
			return;
		}
	}

	this->m_pFmodSystem->playSound(pAudio->m_pSound, 0, false, &pAudio->m_pChannel);
	pAudio->m_pChannel->setVolume(a_fVolume);
}

void CAudioManager::Stop(tstring a_strName)
{
	CAudio* pAudio = this->FindAudio(a_strName);
	if (pAudio == NULL)
	{
		return;
	}

	if (pAudio->m_pChannel == NULL)
	{
		return;
	}
	pAudio->m_pChannel->stop();
	pAudio->m_pChannel = NULL;
}

void LoadAudioCallBack(void* a_pCustomData, CAssetObject* a_pObject)
{
	tstring strName = (tcchar*)a_pCustomData;
	if (MUFFIN.GetAudioMgr()->FindAudio(strName) != NULL)
	{
		return;
	}
	MUFFIN.GetAudioMgr()->AddAudio(strName, (CAudio*)a_pObject);
}
