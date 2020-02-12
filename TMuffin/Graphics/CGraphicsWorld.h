#pragma once
#include "TMuffinSysInclude.h"

class CSkyBox;
class CGraphicsComponent;
class CGraphicsWorld
{
private:
	hash_map<u64, CGraphicsComponent*> m_mapID2GraphicsObj;
	CSkyBox* m_pSkyBox;

public:
	CGraphicsWorld();
	~CGraphicsWorld();

	void AddGraphicsObject(CGraphicsComponent* a_pComponent);
	void RemoveGraphicsObject(CGraphicsComponent* a_pComponent);
	CGraphicsComponent* FindObject(u64 a_nGUID);

	void SetSkyBox(CSkyBox* a_pSkyBox);

	void GraphicsLoop();
	void RenderSkyBox(glm::mat4 a_matV, glm::mat4 a_matP);
};
