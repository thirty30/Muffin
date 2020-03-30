#pragma once

enum EAssetType
{
	EAT_MESH,
	EAT_TEXTURE,
	EAT_MATERIAL,
	EAT_ANIMATION,
};

class T_DLL_EXPORT CAssetObject
{
private:
	EAssetType m_eAssetType;

protected:
	virtual tbool LoadToMemory(const tcchar* a_strFileName) T_PURE;
	virtual tbool InitAfterLoad() T_PURE;

	friend class CAssetsLoader;
	friend class CAssetsWorker;
	friend class CAssetsPool;

public:
	CAssetObject(EAssetType a_eType) 
		: m_eAssetType(a_eType)
	{}
	virtual ~CAssetObject() {}

	T_INLINE EAssetType GetAssetType() { return this->m_eAssetType; }
	
};

