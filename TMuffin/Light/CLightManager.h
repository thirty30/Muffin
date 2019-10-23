#pragma once

class CLightManager
{
private:
	hash_map<u64, CLight*> m_mapID2Light;
	u64 m_nGUIDIDX;

private:
	inline u64 GetGUID() { return ++this->m_nGUIDIDX; }

public:
	CLightManager();
	~CLightManager();

	void AddLight(CLight* a_pLight);
	void DeleteLight(CLight* a_pLight);
	CLight* FindLight(u64 a_nGUID);

	void RenderLights(n32 a_nShaderProgramID);
};



