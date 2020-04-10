#include "CAudio.h"
#include "Engine/Engine.h"
#include "Audio/CAudioManager.h"


CAudio::CAudio() : CAssetObject(EAT_AUDIO)
{
	this->m_nAudioSize = 0;
	this->m_pAudioData = NULL;
	this->m_pSound = NULL;
	this->m_pChannel = NULL;
}

CAudio::~CAudio()
{

}

void CAudio::Clear()
{
	if (this->m_pChannel != NULL)
	{
		this->m_pChannel->stop();
	}
	if (this->m_pSound != NULL)
	{
		//this->m_pSound->release();
	}
	if (this->m_pAudioData != NULL)
	{
		delete this->m_pAudioData;
		this->m_pAudioData = NULL;
	}

}

tbool CAudio::LoadToMemory(const tcchar* a_strFileName)
{
	ifstream objShaderFile(a_strFileName, ifstream::in | ios::binary);
	if (objShaderFile.is_open() == false)
	{
		return false;
	}
	objShaderFile.seekg(0, ios::end);
	this->m_nAudioSize = objShaderFile.tellg();
	objShaderFile.seekg(0);
	this->m_pAudioData = new tcchar[this->m_nAudioSize];
	TMemzero(this->m_pAudioData, this->m_nAudioSize);
	objShaderFile.read(this->m_pAudioData, this->m_nAudioSize);
	objShaderFile.close();
	return true;
}

tbool CAudio::InitAfterLoad()
{
	FMOD::System* pSystem = MUFFIN.GetAudioMgr()->GetFMODSystem();
	FMOD_CREATESOUNDEXINFO exinfo = {0};
	exinfo.cbsize = sizeof(exinfo);
	exinfo.length = this->m_nAudioSize;
	FMOD_RESULT res = pSystem->createSound(this->m_pAudioData, FMOD_OPENMEMORY, &exinfo, &this->m_pSound);
	return true;
}

