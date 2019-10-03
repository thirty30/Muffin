#include "stdafx.h"

tbool CTConfigByCfg::analysis()
{
	if (m_file.canRead() == false)
	{
		return false;
	}
	tcchar sBuffer[LINE_MAX_LEN];
	while (true)
	{
		TMemzero(sBuffer, sizeof(sBuffer));
		if (m_file.readLine(sBuffer, LINE_MAX_LEN) == NULL)
		{
			break;
		}
		if (sBuffer[0] == '#')
		{
			continue;
		}
		n32 nLineLen = (n32)strlen(sBuffer);
		tstring sKey;
		tstring sValue;
		tbool bIsKey = true;
		for (n32 i = 0; i < nLineLen; i++)
		{
			tcchar c = sBuffer[i];
			if (c == '#')
			{
				break;
			}
			//È¥µô¿Õ¸ñ
			if (c == ' ' || c == '\t')
			{
				continue;
			}
			if (c == '\r' || c == '\n')
			{
				break;
			}
			if (c == '=')
			{
				bIsKey = false;
				continue;
			}
			if (bIsKey == true)
			{
				sKey += c;
			}
			else
			{
				sValue += c;
			}
		}
		if (sKey.size() > 0 && sValue.size() <= 0)
		{
			return false;
		}
		if (sKey.size() > 0 && sValue.size() > 0)
		{
			m_hMap.insert(make_pair(sKey, sValue));
		}
	}
	return true;
}

tstring CTConfigByCfg::getValue( const tcchar* a_sKey )
{
	tstring sKey(a_sKey);
	hash_map<tstring, tstring>::const_iterator iter = m_hMap.find(sKey);
	if (iter != m_hMap.end())
	{
		return iter->second;
	}
	return "";
}

n32 CTConfigByCfg::getN32( const tcchar* a_sKey )
{
	tstring sKey(a_sKey);
	hash_map<tstring, tstring>::const_iterator iter = m_hMap.find(sKey);
	if (iter == m_hMap.end())
	{
		return 0;
	}
	tstring sValue = iter->second;
	return TA2N32(sValue.c_str());
}

f32 CTConfigByCfg::getF32( const tcchar* a_sKey )
{
	tstring sKey(a_sKey);
	hash_map<tstring, tstring>::const_iterator iter = m_hMap.find(sKey);
	if (iter == m_hMap.end())
	{
		return 0.0f;
	}
	tstring sValue = iter->second;
	return (f32)TA2F(sValue.c_str());
}
