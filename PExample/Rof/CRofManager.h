#pragma once

class CRofTableBase
{
public:
	virtual n32 ReadBody(const tcchar* a_pData, n32 a_nOffset) T_PURE;
};

#include "./TRofTableDefine.h"
#include "./RofTable.h"

#include "./TRofTableSerializeDefine.h"
#include "./RofTable.h"

#undef ROF_TABLE_HEAD
#undef COLUMN_ITEM
#undef ROF_TABLE_TAIL

template<typename T>
class CRofHolder
{
	n32 m_nColNum;
	n32 m_nRowNum;
	hash_map<n32, T*> m_map;

public:
	CRofHolder() :
		m_nColNum(0),
		m_nRowNum(0)
	{

	}
	tbool Init(tcchar* a_pReadBuffer, const tstring a_pPath)
	{
		CFileObject FileHelper;
		if (FileHelper.open(a_pPath.c_str(), E_FILE_B_READ) == false)
		{
			return false;
		}

		n32 nFileLength = FileHelper.getFileSize();
		if (FileHelper.readBuffer(a_pReadBuffer, nFileLength) == false)
		{
			return false;
		}
		n32 nOffset = 64;
		tcchar* pStart = a_pReadBuffer + nOffset;

		////////////////////////////////解析文件头--start//////////////////////////////

		TMemcpy((tcchar*)(&m_nRowNum), sizeof(m_nRowNum), pStart, 4); nOffset += 4;
		pStart = a_pReadBuffer + nOffset;
		TMemcpy((tcchar*)(&m_nColNum), sizeof(m_nColNum), pStart, 4); nOffset += 4;
		pStart = a_pReadBuffer + nOffset;

		for (n32 i = 0; i < m_nColNum; i++)
		{
			n32 nNameLen = 0;
			TMemcpy((tcchar*)(&nNameLen), sizeof(nNameLen), pStart, 1);
			nOffset += 1 + nNameLen;
			pStart = a_pReadBuffer + nOffset;

			n32 nTypeLen = 0;
			TMemcpy((tcchar*)(&nTypeLen), sizeof(nTypeLen), pStart, 1);
			nOffset += 1 + nTypeLen;
			pStart = a_pReadBuffer + nOffset;
		}
		////////////////////////////////解析文件头--end//////////////////////////////

		///////////////////////////////解析行--start//////////////////////
		for (n32 i = 0; i < m_nRowNum; i++)
		{
			n32 nID = 0;
			TMemcpy((tcchar*)(&nID), sizeof(nID), pStart, 4);
			T* pModel = new T();
			n32 nTemp = pModel->ReadBody(pStart, nFileLength - nOffset);
			if (nTemp == -1)
			{
				return false;
			}
			nOffset += nTemp;
			pStart = a_pReadBuffer + nOffset;
			m_map[nID] = pModel;
		}
		///////////////////////////////解析行--end////////////////////////


		FileHelper.close();
		return true;
	}

	n32 GetColNum()
	{
		return m_nColNum;
	}

	n32 GetRowNum()
	{
		return m_nRowNum;
	}

	T* GetDataByID(n32 a_nID)
	{
		typename hash_map<n32, T*>::const_iterator iter = m_map.find(a_nID);
		if (iter != m_map.end())
		{
			return iter->second;
		}
		return NULL;
	}

};

#define MAX_ROF_SIZE 1024*100
class CRofManager
{
private:
	CRofHolder<CRofSceneItem> m_rofSceneItem;
	CRofHolder<CRofScene> m_rofScene;
	CRofHolder<CRofLight> m_rofLight;


public:
	tbool Init(tstring a_sResPath)
	{
		return true;

		tcchar* pBuffer = new tcchar[MAX_ROF_SIZE];

		if (m_rofSceneItem.Init(pBuffer, a_sResPath + "RofSceneItem.bytes") == false) { return false; }
		if (m_rofScene.Init(pBuffer, a_sResPath + "RofGraphicsScene2.bytes") == false) { return false; }
		if (m_rofLight.Init(pBuffer, a_sResPath + "RofGraphicsLight.bytes") == false) { return false; }

		delete[] pBuffer;
		return true;
	}

	CRofHolder<CRofSceneItem>& GetSceneItem() { return this->m_rofSceneItem; }
	CRofHolder<CRofScene>& GetScene() { return this->m_rofScene; }
	CRofHolder<CRofLight>& GetLight() { return this->m_rofLight; }

	void Clear()
	{
		// TODO: release Holder memory
	}

};











