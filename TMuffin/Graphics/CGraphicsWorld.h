#pragma once
#include "TMuffinSysInclude.h"
#include "Gizmo/CGizmo.h"

class CCamera;
class CSkyBox;
class CGraphicsComponent;
class CFBOComponent;
class CGraphicsWorld
{
private:
	hash_map<u64, CGraphicsComponent*> m_mapID2GraphicsObj;
	hash_map<u64, CFBOComponent*> m_mapID2FBOObj;
	CSkyBox* m_pSkyBox;
	vector<CGizmo> m_vecGizmo;

public:
	CGraphicsWorld();
	~CGraphicsWorld();

	void AddGraphicsObject(CGraphicsComponent* a_pComponent);
	void RemoveGraphicsObject(CGraphicsComponent* a_pComponent);
	CGraphicsComponent* FindObject(u64 a_nGUID);

	void AddFBOObject(CFBOComponent* a_pComponent);
	void RemoveFBOObject(CFBOComponent* a_pComponent);

	void SetSkyBox(CSkyBox* a_pSkyBox);

	void GraphicsLoop();
	void RenderSkyBox(glm::mat4 a_matV, glm::mat4 a_matP);
	void RenderObject(CCamera* a_pCamera);
	void RenderFBO();

	void DrawLine(glm::vec3 a_vStartPoint, glm::vec3 a_vEndPoint, glm::vec3 a_vColor, f32 a_fLineWidth);
	
};
