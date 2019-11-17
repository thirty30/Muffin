#pragma once

class CGraphicsRenderer
{
private:
	hash_map<u64, CGraphicsObject*> m_mapID2GraphicsObj;
	CSkyBox* m_pSkyBox;

public:
	CGraphicsRenderer();
	~CGraphicsRenderer();

	void AddObject(CGraphicsObject* a_pObject);
	void RemoveObject(CGraphicsObject* a_pObject);
	CGraphicsObject* FindObject(u64 a_nGUID);

	void SetSkyBox(CSkyBox* a_pSkyBox);

	void GraphicsLoop();
	void RenderSkyBox(glm::mat4 a_matV, glm::mat4 a_matP);
};
