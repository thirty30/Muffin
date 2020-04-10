#pragma once
#include "TMuffinSysInclude.h"
#include "CAssetObject.h"
#include <fmod/fmod.hpp>

class CAudio : public CAssetObject
{
public:

	n32 m_nAudioSize;
	tcchar* m_pAudioData;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

public:
	CAudio();
	~CAudio();

	void Clear();

protected:
	virtual tbool LoadToMemory(const tcchar* a_strFileName) override;
	virtual tbool InitAfterLoad();
};


