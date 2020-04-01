#include "CColliderCloth.h"

CColliderCloth::CColliderCloth() : CColliderBase(E_CLOTH_COLLIDER)
{
	this->m_fRadius = 0;
	this->m_vecNodes.clear();
}

CColliderCloth::~CColliderCloth()
{

}

void CColliderCloth::Init(SClothInfo& a_rInfo)
{
	n32 nTotalNodeNum = a_rInfo.m_nNodeNumAcross * a_rInfo.m_nNodeNumDown;
	this->m_vecNodes.clear();
	this->m_vecNodes.resize(nTotalNodeNum);

	n32 nIdx = 0;
	glm::vec3 vSepAcross = a_rInfo.m_vCornerB - a_rInfo.m_vCornerA;
	vSepAcross /= (a_rInfo.m_nNodeNumAcross - 1);

	glm::vec3 vSepDown = glm::normalize(a_rInfo.m_vDownDir);
	vSepDown *= glm::length(vSepAcross);

	//set the node position
	for (n32 i = 0; i < a_rInfo.m_nNodeNumAcross; i++)
	{
		for (n32 j = 0; j < a_rInfo.m_nNodeNumDown; j++)
		{
			this->m_vecNodes[nIdx] = a_rInfo.m_vCornerA + vSepAcross * (f32)i + vSepDown * (f32)j;
			nIdx++;
		}
	}
	this->m_fRadius = glm::length(vSepAcross) / 2;
}

glm::vec3 CColliderCloth::GetMinPoint()
{
	return this->m_vecNodes[this->m_vecNodes.size() - 1] - glm::vec3(this->m_fRadius, this->m_fRadius, this->m_fRadius);
}

glm::vec3 CColliderCloth::GetMaxPoint()
{
	return this->m_vecNodes[0] + glm::vec3(this->m_fRadius, this->m_fRadius, this->m_fRadius);
}

n32 CColliderCloth::GetNodeNum()
{
	return this->m_vecNodes.size();
}

f32 CColliderCloth::GetNodeRadius()
{
	return this->m_fRadius;
}

void CColliderCloth::SetPostion(n32 a_nIdx, glm::vec3 a_vPostion)
{
	this->m_vecNodes[a_nIdx] = a_vPostion;
}

n32 CColliderCloth::IntegrateNode(glm::vec3 a_vPostion, f32 a_fRadius)
{
	for (n32 i = 0; i < this->m_vecNodes.size(); i++)
	{
		glm::vec3 vNodePosition = this->m_vecNodes[i];
		f32 fDis = glm::distance(vNodePosition, a_vPostion);
		if (fDis <= a_fRadius + this->m_fRadius)
		{
			return i;
		}
	}
	return -1;
}

