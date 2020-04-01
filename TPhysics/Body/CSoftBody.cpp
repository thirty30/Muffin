#include "CSoftBody.h"

CSoftBodyNode::CSoftBodyNode()
{
	this->m_fMass = 0;
	this->m_fRadius = 0;
	this->m_vPosition = glm::vec3(0, 0, 0);
	this->m_vVelocity = glm::vec3(0, 0, 0);
	this->m_vAcceleration = glm::vec3(0, 0, 0);
	this->m_vForce = glm::vec3(0, 0, 0);
	this->m_vecNeighbor.clear();
}

CSoftBodyNode::~CSoftBodyNode()
{

}

tbool CSoftBodyNode::IsFixed()
{
	return (this->m_fMass == 0);
}

tbool CSoftBodyNode::IsNeighbor(n32 a_nIdx)
{
	for (n32 i = 0; i < this->m_vecNeighbor.size(); i++)
	{
		if (a_nIdx == this->m_vecNeighbor[i])
		{
			return true;
		}
	}
	return false;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSoftBodySpring::CSoftBodySpring()
{
	this->m_pNodeA = NULL;
	this->m_pNodeB = NULL;
	this->m_fRestingLength = 0;
	this->m_fSpringConstant = 0;
	this->m_vCurrentForceA2B = glm::vec3(0, 0, 0);
}

CSoftBodySpring::~CSoftBodySpring()
{

}

void CSoftBodySpring::Init(CSoftBodyNode* a_pNodeA, CSoftBodyNode* a_pNodeB, f32 a_fConstant)
{
	this->m_pNodeA = a_pNodeA;
	this->m_pNodeB = a_pNodeB;
	this->m_fRestingLength = glm::distance(this->m_pNodeA->m_vPosition, this->m_pNodeB->m_vPosition);
	this->m_fSpringConstant = a_fConstant;
	this->m_vCurrentForceA2B = glm::vec3(0, 0, 0);
}

void CSoftBodySpring::UpdateSpringForce()
{
	glm::vec3 vSep = this->m_pNodeA->m_vPosition - this->m_pNodeB->m_vPosition;
	f32 fDis = glm::length(vSep);
	f32 fOffsetX = fDis - this->m_fRestingLength;
	this->m_vCurrentForceA2B = glm::normalize(vSep) * this->m_fSpringConstant * fOffsetX;	//f = kx
}

void CSoftBodySpring::ApplyForce()
{
	if (this->m_pNodeA->IsFixed() == false)
	{
		this->m_pNodeA->m_vAcceleration -= this->m_vCurrentForceA2B / this->m_pNodeA->m_fMass;
	}
	if (this->m_pNodeB->IsFixed() == false)
	{
		this->m_pNodeB->m_vAcceleration += this->m_vCurrentForceA2B / this->m_pNodeB->m_fMass;
	}
}

CSoftBodyNode* CSoftBodySpring::GetOther(CSoftBodyNode* a_pNode)
{
	return a_pNode == this->m_pNodeA ? this->m_pNodeB : this->m_pNodeA;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSoftBody::CSoftBody() : CBodyBase(E_SOFT_BODY)
{
	this->m_vecNodes.clear();
	this->m_vecSprings.clear();
}

CSoftBody::~CSoftBody()
{
	this->m_vecNodes.clear();
	this->m_vecSprings.clear();
}

void CSoftBody::Init(SClothInfo& a_rInfo)
{
	n32 nAcrossNum = a_rInfo.m_nNodeNumAcross;
	n32 nDownNum = a_rInfo.m_nNodeNumDown;

	n32 nTotalNodeNum = nAcrossNum * nDownNum;
	this->m_vecNodes.resize(nTotalNodeNum);

	n32 nTotalSpringNum = nAcrossNum * (nDownNum - 1) + nDownNum * (nAcrossNum - 1);
	this->m_vecSprings.resize(nTotalSpringNum);

	glm::vec3 vSepAcross = a_rInfo.m_vCornerB - a_rInfo.m_vCornerA;
	vSepAcross /= (nAcrossNum - 1);

	glm::vec3 vSepDown = glm::normalize(a_rInfo.m_vDownDir);
	vSepDown *= glm::length(vSepAcross);

	f32 fRadius = glm::length(vSepAcross) * 0.5f;

	//set the node information
	n32 nIdx = 0;
	for (n32 i = 0; i < nAcrossNum; i++)
	{
		for (n32 j = 0; j < nDownNum; j++)
		{
			this->m_vecNodes[nIdx].m_vPosition = a_rInfo.m_vCornerA + vSepAcross * (f32)i + vSepDown * (f32)j;
			this->m_vecNodes[nIdx].m_fMass = a_rInfo.m_fNodeMass;
			if (j == 0)
			{
				this->m_vecNodes[nIdx].m_fMass = 0;
			}
			this->m_vecNodes[nIdx].m_fRadius = fRadius;
			nIdx++;
		}
	}
	//corner point set fixed
	//this->m_vecNodes[0].m_fMass = 0;
	//this->m_vecNodes[(nAcrossNum - 1) * nDownNum].m_fMass = 0;

	nIdx = 0;
	//set the spring information
	//1.set down springs
	for (n32 i = 0; i < nAcrossNum; i++)
	{
		for (n32 j = 0; j < nDownNum - 1; j++)
		{
			n32 nColID = i * nDownNum;
			n32 nRowID = j;
			CSoftBodyNode* pNodeA = &this->m_vecNodes[nColID + nRowID];
			CSoftBodyNode* pNodeB = &this->m_vecNodes[nColID + nRowID + 1];

			pNodeA->m_vecNeighbor.push_back(nColID + nRowID + 1);
			pNodeB->m_vecNeighbor.push_back(nColID + nRowID);

			this->m_vecSprings[nIdx].Init(pNodeA, pNodeB, a_rInfo.m_fSpringConstant);
			nIdx++;
		}
	}
	//2.set across springs
	for (n32 i = 0; i < nDownNum; i++)
	{
		for (n32 j = 0; j < nAcrossNum - 1; j++)
		{
			n32 nColIDA = j * nDownNum;
			n32 nRowIDA = i;
			CSoftBodyNode* pNodeA = &this->m_vecNodes[nColIDA + nRowIDA];
			n32 nColIDB = (j + 1) * nDownNum;
			n32 nRowIDB = i;
			CSoftBodyNode* pNodeB = &this->m_vecNodes[nColIDB + nRowIDB];

			pNodeA->m_vecNeighbor.push_back(nColIDB + nRowIDB);
			pNodeB->m_vecNeighbor.push_back(nColIDA + nRowIDA);

			this->m_vecSprings[nIdx].Init(pNodeA, pNodeB, a_rInfo.m_fSpringConstant);
			nIdx++;
		}
	}
}

n32 CSoftBody::GetNodeNum()
{
	return this->m_vecNodes.size();
}

f32 CSoftBody::GetNodeRadius(n32 a_nIdx)
{
	if (a_nIdx >= this->m_vecNodes.size())
	{
		return 0;
	}
	return this->m_vecNodes[a_nIdx].m_fRadius;
}

glm::vec3 CSoftBody::GetNodePostion(n32 a_nIdx)
{
	if (a_nIdx >= this->m_vecNodes.size())
	{
		return glm::vec3(0, 0, 0);
	}
	return this->m_vecNodes[a_nIdx].m_vPosition;
}

void CSoftBody::ClearAccelaration()
{

}

void CSoftBody::Update(f32 a_fDelatTime, const glm::vec3& a_vGravity)
{
	// 1. add gravity and other force
	for (n32 i = 0; i < this->GetNodeNum(); i++)
	{
		CSoftBodyNode& rNode = this->m_vecNodes[i];
		if (rNode.IsFixed() == true)
		{
			continue;
		}
		rNode.m_vAcceleration = a_vGravity + rNode.m_vForce / rNode.m_fMass;
		rNode.m_vForce *= 0;
	}
	
	// 2. calc spring force
	for (n32 i = 0; i < this->m_vecSprings.size(); i++)
	{
		this->m_vecSprings[i].UpdateSpringForce();
		this->m_vecSprings[i].ApplyForce();
	}
	
	// 3. calc node position
	for (n32 i = 0; i < this->GetNodeNum(); i++)
	{
		CSoftBodyNode& rNode = this->m_vecNodes[i];
		if (rNode.IsFixed() == true)
		{
			continue;
		}
		rNode.m_vVelocity += rNode.m_vAcceleration * a_fDelatTime;
		rNode.m_vPosition += rNode.m_vVelocity * a_fDelatTime;
		rNode.m_vVelocity *= glm::pow(0.6f, a_fDelatTime);
	}

	// 4. calc node collision
	for (n32 i = 0; i < this->m_vecNodes.size() - 1; i++)
	{
		for (n32 j = i + 1; j < this->m_vecNodes.size(); j++)
		{
			CSoftBodyNode& rNodeA = this->m_vecNodes[i];
			CSoftBodyNode& rNodeB = this->m_vecNodes[j];
			if (rNodeA.IsNeighbor(j) == true)
			{
				continue;
			}

			f32 fDis = glm::distance(rNodeA.m_vPosition, rNodeB.m_vPosition);
			if (fDis <= rNodeA.m_fRadius + rNodeB.m_fRadius)
			{
				f32 fDepth = rNodeA.m_fRadius + rNodeB.m_fRadius - fDis;
				glm::vec3 vDir = glm::normalize(rNodeA.m_vPosition - rNodeB.m_vPosition);
				//pNodeA->m_vPosition += 0.5f * fDepth * vDir;
				rNodeB.m_vPosition += fDepth * (-vDir);
				glm::vec3 vNodeAVelocity = rNodeA.m_vVelocity;
				rNodeA.m_vVelocity = rNodeB.m_vVelocity * 0.9f;
				rNodeB.m_vVelocity = vNodeAVelocity * 0.9f;
			}
		}
	}
}

void CSoftBody::AddForce(glm::vec3 a_vForce, n32 a_nIdx)
{
	this->m_vecNodes[a_nIdx].m_vForce += a_vForce;
}

CSoftBodyNode* CSoftBody::GetNode(n32 a_nIdx)
{
	return &this->m_vecNodes[a_nIdx];
}

