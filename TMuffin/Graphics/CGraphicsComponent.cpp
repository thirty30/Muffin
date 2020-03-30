#include "CGraphicsComponent.h"
#include "CGraphicsWorld.h"
#include "AssetsLoader/AssetObject/CMaterial.h"
#include "AssetsLoader/AssetObject/CMesh.h"
#include "AssetsLoader/CAssetsLoader.h"
#include "Engine/Engine.h"
#include "Utility/CGUIDMaker.h"
#include "Light/CLightManager.h"

CGraphicsComponent::CGraphicsComponent()
{
	this->m_nRenderMode = GL_FILL;
	this->m_pMesh = NULL;
	this->m_pMaterial = NULL;
}

CGraphicsComponent::~CGraphicsComponent()
{
	if (this->m_pMesh != NULL)
	{
		//delete todo
		this->m_pMesh = NULL;
	}
	if (this->m_pMaterial != NULL)
	{
		//delete todo
		this->m_pMaterial = NULL;
	}
	MUFFIN.GetGraphicsWorld()->RemoveGraphicsObject(this);
}

void CGraphicsComponent::Init()
{
	if (this->m_pMesh == NULL)
	{
		if (this->m_strMeshFile.empty() == true)
		{
			return;
		}
		this->m_pMesh = CAssetsLoader::Load<CMesh>(this->m_strMeshFile.c_str());
		if (this->m_pMesh == NULL)
		{
			return;
		}
	}

	if (this->m_pMaterial == NULL)
	{
		if (this->m_strMaterialFile.empty() == true)
		{
			return;
		}
		this->m_pMaterial = CAssetsLoader::Load<CMaterial>(this->m_strMaterialFile.c_str());
		if (this->m_pMaterial == NULL)
		{
			return;
		}
	}
	MUFFIN.GetGraphicsWorld()->AddGraphicsObject(this);
	n32 nShaderProgramID = this->m_pMaterial->GetShaderID();

	glBindVertexArray(this->m_pMesh->GetVAOID());
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pMesh->GetVertexBufferID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_pMesh->GetTriangleBufferID());

	// Set the vertex attributes for this shader
	GLint nPositionLocation = glGetAttribLocation(nShaderProgramID, "vPosition");
	glEnableVertexAttribArray(nPositionLocation);
	glVertexAttribPointer(nPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, x)));
	

	GLint nColorLocation = glGetAttribLocation(nShaderProgramID, "vColor");
	glEnableVertexAttribArray(nColorLocation);
	glVertexAttribPointer(nColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, r)));

	GLint nNormalLocation = glGetAttribLocation(nShaderProgramID, "vNormal");
	glEnableVertexAttribArray(nNormalLocation);
	glVertexAttribPointer(nNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, nx)));

	GLint nUVLocation = glGetAttribLocation(nShaderProgramID, "vUVx2");
	glEnableVertexAttribArray(nUVLocation);
	glVertexAttribPointer(nUVLocation, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, u0)));

	GLint nTangent = glGetAttribLocation(nShaderProgramID, "vTangent");
	glEnableVertexAttribArray(nTangent);
	glVertexAttribPointer(nTangent, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, tx)));

	GLint nBiNormal = glGetAttribLocation(nShaderProgramID, "vBiNormal");
	glEnableVertexAttribArray(nBiNormal);
	glVertexAttribPointer(nBiNormal, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, bx)));

	GLint nBoneID = glGetAttribLocation(nShaderProgramID, "vBoneID");
	glEnableVertexAttribArray(nBoneID);
	glVertexAttribPointer(nBoneID, 4, GL_INT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, boneID[0])));

	GLint nBoneWeight = glGetAttribLocation(nShaderProgramID, "vBoneWeight");
	glEnableVertexAttribArray(nBoneWeight);
	glVertexAttribPointer(nBoneWeight, 4, GL_FLOAT, GL_FALSE, sizeof(SMeshVertex), (void*)(offsetof(SMeshVertex, boneWeight[0])));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(nPositionLocation);
	glDisableVertexAttribArray(nColorLocation);
	glDisableVertexAttribArray(nNormalLocation);
	glDisableVertexAttribArray(nUVLocation);
	glDisableVertexAttribArray(nTangent);
	glDisableVertexAttribArray(nBiNormal);
	glDisableVertexAttribArray(nBoneID);
	glDisableVertexAttribArray(nBoneWeight);
}

void CGraphicsComponent::SetRenderMode(ERenderMode a_eMode)
{
	if (a_eMode == E_RENDER_MODE_POINT)
	{
		this->m_nRenderMode = GL_POINT;
	}
	else if (a_eMode == E_RENDER_MODE_LINE)
	{
		this->m_nRenderMode = GL_LINE;
	}
	else
	{
		this->m_nRenderMode = GL_FILL;
	}
}
