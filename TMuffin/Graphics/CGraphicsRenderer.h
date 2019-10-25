#pragma once

class CGraphicsRenderer
{
private:
	hash_map<u64, CGraphicsObject*> m_mapID2GraphicsObj;

public:
	CGraphicsRenderer();
	~CGraphicsRenderer();

	void AddObject(CGraphicsObject* a_pObject);
	void RemoveObject(CGraphicsObject* a_pObject);
	CGraphicsObject* FindObject(u64 a_nGUID);

	void GraphicsLoop();
};
