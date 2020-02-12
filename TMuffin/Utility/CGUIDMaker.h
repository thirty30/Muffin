#pragma once
#include "TMuffinSysInclude.h"
#include "CommonDefine.h"

class CGUIDMaker
{
private:
	u32 m_nLen;
	u64* m_nCounter;

public:
	CGUIDMaker(u32 a_nIDTypeNum)
	{
		this->m_nLen = a_nIDTypeNum;
		this->m_nCounter = new u64[a_nIDTypeNum];
		TMemzero(this->m_nCounter, sizeof(u64) * a_nIDTypeNum);
	}

	~CGUIDMaker()
	{
		delete this->m_nCounter;
	}

	T_INLINE u64 GenerateGUID(u32 a_nType)
	{
		if (a_nType < 0 || a_nType >= this->m_nLen)
		{
			return 0;
		}
		this->m_nCounter[a_nType]++;
		return ((u64)a_nType << 48) + this->m_nCounter[a_nType];
	}
};

