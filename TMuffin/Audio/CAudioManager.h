#pragma once
#include <fmod/fmod.hpp>
#include "TMuffinSysInclude.h"
#include "AssetsLoader/AssetsInclude.h"

class CAudioManager
{
private:
	FMOD::System* m_pFmodSystem;
	hash_map<tstring, CAudio*> m_mapAudio;

public:
	CAudioManager();
	~CAudioManager();

	tbool Init();
	void Clear();
	void LoadAudio(tstring a_strName, const tcchar* a_pFile);
	void LoadAudioASync(tstring a_strName, const tcchar* a_pFile);
	CAudio* FindAudio(tstring a_strName);
	void AddAudio(tstring a_strName, CAudio* a_pAudio);
	FMOD::System* GetFMODSystem() { return this->m_pFmodSystem; }
	void Play(tstring a_strName, tbool a_bIsLoop, f32 a_fVolume);
	void Stop(tstring a_strName);
};

extern void LoadAudioCallBack(void* a_pCustomData, CAssetObject* a_pObject);

