#pragma once

class CGUIDMaker
{
private:
	u64 m_nCounter[E_GUID_TYPE_MAX];

public:
	CGUIDMaker()
	{
		TMemzero(this->m_nCounter, sizeof(u64) * E_GUID_TYPE_MAX);
	}

	T_INLINE u64 GenerateGUID(EGUIDType a_eType)
	{
		if (a_eType <= E_GUID_TYPE_INIT || a_eType >= E_GUID_TYPE_MAX)
		{
			return 0;
		}
		this->m_nCounter[a_eType]++;
		return ((u64)a_eType << 48) + this->m_nCounter[a_eType];
	}
};




