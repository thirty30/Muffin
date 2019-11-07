#include "pch.h"

CColliderMesh::CColliderMesh() : CColliderBase(E_COLLIDER_TYPE_MESH)
{
	this->m_nTriangleCount = 0;
	this->m_pTriangleoArray = NULL;
	this->m_vMinPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vMaxPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_nXStepNum = 10;
	this->m_nYStepNum = 10;
	this->m_nZStepNum = 10;
	this->m_fXStep = 0;
	this->m_fYStep = 0;
	this->m_fZStep = 0;
	this->m_mapID2AABB.clear();
}

CColliderMesh::~CColliderMesh()
{
	hash_map<u64, SMeshColliderBox*>::const_iterator iter = this->m_mapID2AABB.begin();
	for (; iter != this->m_mapID2AABB.end(); iter++)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
		}
	}
}

SMeshColliderBox* CColliderMesh::GetBoxByID(u64 a_nID)
{
	hash_map<u64, SMeshColliderBox*>::const_iterator iter = this->m_mapID2AABB.find(a_nID);
	if (iter != this->m_mapID2AABB.end())
	{
		return iter->second;
	}
	SMeshColliderBox* pBox = new SMeshColliderBox();
	u64 nMinXNum = a_nID / 100000000;
	u64 nMinYNum = (a_nID - nMinXNum * 100000000) / 10000;
	u64 nMinZNum = a_nID - nMinXNum * 100000000 - nMinYNum * 10000;
	pBox->m_fMinPoint = glm::vec3(nMinXNum * this->m_fXStep, nMinYNum * this->m_fYStep, nMinZNum * this->m_fZStep) + this->m_vMinPoint;
	pBox->m_fMaxPoint = glm::vec3((nMinXNum + 1) * this->m_fXStep, (nMinYNum + 1) * this->m_fYStep, (nMinZNum + 1) * this->m_fZStep) + this->m_vMinPoint;
	this->m_mapID2AABB[a_nID] = pBox;
	return pBox;
}

SMeshColliderBox* CColliderMesh::FindBoxByPosition(glm::vec3 a_vPosition)
{
	glm::vec3 vOffsetPoint = a_vPosition - this->m_vMinPoint;
	u64 nXNum = (u64)(vOffsetPoint.x / this->m_fXStep); if (nXNum == this->m_nXStepNum) { nXNum -= 1; }
	u64 nYNum = (u64)(vOffsetPoint.y / this->m_fYStep); if (nYNum == this->m_nYStepNum) { nYNum -= 1; }
	u64 nZNum = (u64)(vOffsetPoint.z / this->m_fZStep); if (nZNum == this->m_nZStepNum) { nZNum -= 1; }
	u64 nID = nXNum * 100000000 + nYNum * 10000 + nZNum;
	hash_map<u64, SMeshColliderBox*>::const_iterator iter = this->m_mapID2AABB.find(nID);
	if (iter != this->m_mapID2AABB.end())
	{
		return iter->second;
	}
	return NULL;
}

void CColliderMesh::InitColliderMesh(CMesh* a_pMesh)
{
	f32 fMinX = FLT_MAX, fMinY = FLT_MAX, fMinZ = FLT_MAX;
	f32 fMaxX = FLT_MIN, fMaxY = FLT_MIN, fMaxZ = FLT_MIN;

	this->m_nTriangleCount = a_pMesh->m_nTriangleCount;
	this->m_pTriangleoArray = new SMeshColliderTriangle[this->m_nTriangleCount];
	for (n32 i = 0; i < this->m_nTriangleCount; i++)
	{
		SMeshTriangle* pTriangle = &a_pMesh->m_pTriangles[i];
		SMeshColliderTriangle* pInfo = &this->m_pTriangleoArray[i];
		pInfo->m_vPoint1.x = a_pMesh->m_pVertices[pTriangle->Vertex1].x + this->m_vCenter.x;
		pInfo->m_vPoint1.y = a_pMesh->m_pVertices[pTriangle->Vertex1].y + this->m_vCenter.y;
		pInfo->m_vPoint1.z = a_pMesh->m_pVertices[pTriangle->Vertex1].z + this->m_vCenter.z;

		pInfo->m_vPoint2.x = a_pMesh->m_pVertices[pTriangle->Vertex2].x + this->m_vCenter.x;
		pInfo->m_vPoint2.y = a_pMesh->m_pVertices[pTriangle->Vertex2].y + this->m_vCenter.y;
		pInfo->m_vPoint2.z = a_pMesh->m_pVertices[pTriangle->Vertex2].z + this->m_vCenter.z;

		pInfo->m_vPoint3.x = a_pMesh->m_pVertices[pTriangle->Vertex3].x + this->m_vCenter.x;
		pInfo->m_vPoint3.y = a_pMesh->m_pVertices[pTriangle->Vertex3].y + this->m_vCenter.y;
		pInfo->m_vPoint3.z = a_pMesh->m_pVertices[pTriangle->Vertex3].z + this->m_vCenter.z;

		glm::vec3 vNormal1 = glm::normalize(pInfo->m_vPoint2 - pInfo->m_vPoint1);
		glm::vec3 vNormal2 = glm::normalize(pInfo->m_vPoint3 - pInfo->m_vPoint1);
		pInfo->m_vTriangleNormal = glm::normalize(glm::cross(vNormal1, vNormal2));

		// separate mesh to AABB
		if (pInfo->m_vPoint1.x < fMinX) { fMinX = pInfo->m_vPoint1.x; }
		if (pInfo->m_vPoint1.y < fMinY) { fMinY = pInfo->m_vPoint1.y; }
		if (pInfo->m_vPoint1.z < fMinZ) { fMinZ = pInfo->m_vPoint1.z; }
		if (pInfo->m_vPoint1.x > fMaxX) { fMaxX = pInfo->m_vPoint1.x; }
		if (pInfo->m_vPoint1.y > fMaxY) { fMaxY = pInfo->m_vPoint1.y; }
		if (pInfo->m_vPoint1.z > fMaxZ) { fMaxZ = pInfo->m_vPoint1.z; }

		if (pInfo->m_vPoint2.x < fMinX) { fMinX = pInfo->m_vPoint2.x; }
		if (pInfo->m_vPoint2.y < fMinY) { fMinY = pInfo->m_vPoint2.y; }
		if (pInfo->m_vPoint2.z < fMinZ) { fMinZ = pInfo->m_vPoint2.z; }
		if (pInfo->m_vPoint2.x > fMaxX) { fMaxX = pInfo->m_vPoint2.x; }
		if (pInfo->m_vPoint2.y > fMaxY) { fMaxY = pInfo->m_vPoint2.y; }
		if (pInfo->m_vPoint2.z > fMaxZ) { fMaxZ = pInfo->m_vPoint2.z; }

		if (pInfo->m_vPoint3.x < fMinX) { fMinX = pInfo->m_vPoint3.x; }
		if (pInfo->m_vPoint3.y < fMinY) { fMinY = pInfo->m_vPoint3.y; }
		if (pInfo->m_vPoint3.z < fMinZ) { fMinZ = pInfo->m_vPoint3.z; }
		if (pInfo->m_vPoint3.x > fMaxX) { fMaxX = pInfo->m_vPoint3.x; }
		if (pInfo->m_vPoint3.y > fMaxY) { fMaxY = pInfo->m_vPoint3.y; }
		if (pInfo->m_vPoint3.z > fMaxZ) { fMaxZ = pInfo->m_vPoint3.z; }
	}

	this->m_fXStep = (fMaxX - fMinX) / this->m_nXStepNum;
	if (this->m_fXStep <= 0)
	{
		fMaxX += 1.0f;
		fMinX -= 1.0f;
		this->m_fXStep = 2.0f;
	}
	this->m_fYStep = (fMaxY - fMinY) / this->m_nYStepNum;
	if (this->m_fYStep <= 0)
	{
		fMaxY += 1.0f;
		fMinY -= 1.0f;
		this->m_fYStep = 2.0f;
	}
	this->m_fZStep = (fMaxZ - fMinZ) / this->m_nZStepNum;
	if (this->m_fZStep <= 0)
	{
		fMaxZ += 1.0f;
		fMinZ -= 1.0f;
		this->m_fZStep = 2.0f;
	}

	this->m_vMinPoint = glm::vec3(fMinX, fMinY, fMinZ);
	this->m_vMaxPoint = glm::vec3(fMaxX, fMaxY, fMaxZ);

	for (n32 i = 0; i < this->m_nTriangleCount; i++)
	{
		n32 nTriangleIdx = i;
		SMeshColliderTriangle& rInfo = this->m_pTriangleoArray[nTriangleIdx];
		glm::vec3 vOffsetPoint1 = rInfo.m_vPoint1 - this->m_vMinPoint;
		u64 nXNum1 = (u64)(vOffsetPoint1.x / this->m_fXStep); if (nXNum1 == this->m_nXStepNum) { nXNum1 -= 1; }
		u64 nYNum1 = (u64)(vOffsetPoint1.y / this->m_fYStep); if (nYNum1 == this->m_nYStepNum) { nYNum1 -= 1; }
		u64 nZNum1 = (u64)(vOffsetPoint1.z / this->m_fZStep); if (nZNum1 == this->m_nZStepNum) { nZNum1 -= 1; }
		u64 nID1 = nXNum1 * 100000000 + nYNum1 * 10000 + nZNum1;
		SMeshColliderBox* pBox = this->GetBoxByID(nID1);
		pBox->m_vecTriangleIdx.push_back(nTriangleIdx);

		glm::vec3 vOffsetPoint2 = rInfo.m_vPoint2 - this->m_vMinPoint;
		u64 nXNum2 = (u64)(vOffsetPoint2.x / this->m_fXStep); if (nXNum2 == this->m_nXStepNum) { nXNum2 -= 1; }
		u64 nYNum2 = (u64)(vOffsetPoint2.y / this->m_fYStep); if (nYNum2 == this->m_nYStepNum) { nYNum2 -= 1; }
		u64 nZNum2 = (u64)(vOffsetPoint2.z / this->m_fZStep); if (nZNum2 == this->m_nZStepNum) { nZNum2 -= 1; }
		u64 nID2 = nXNum2 * 100000000 + nYNum2 * 10000 + nZNum2;
		if (nID2 != nID1)
		{
			pBox = this->GetBoxByID(nID2);
			pBox->m_vecTriangleIdx.push_back(nTriangleIdx);

			f32 fDis = glm::distance(rInfo.m_vPoint1, rInfo.m_vPoint2);
			f32 fTempStep = fDis / SUB_STEP_NUM;
			glm::vec3 vDirection = glm::normalize(rInfo.m_vPoint1 - rInfo.m_vPoint2);
			glm::vec3 vLastPoint = rInfo.m_vPoint2;
			u64 nLastID = nID2;
			for (n32 j = 0; j < SUB_STEP_NUM; j++)
			{
				vLastPoint += vDirection * fTempStep;
				glm::vec3 vOffsetPoint = vLastPoint - this->m_vMinPoint;
				u64 nXNumTemp = (u64)(vOffsetPoint.x / this->m_fXStep);	if (nXNumTemp == this->m_nXStepNum) { nXNumTemp -= 1; }
				u64 nYNumTemp = (u64)(vOffsetPoint.y / this->m_fYStep);	if (nYNumTemp == this->m_nYStepNum) { nYNumTemp -= 1; }
				u64 nZNumTemp = (u64)(vOffsetPoint.z / this->m_fZStep);	if (nZNumTemp == this->m_nZStepNum) { nZNumTemp -= 1; }
				u64 nCurID = nXNumTemp * 100000000 + nYNumTemp * 10000 + nZNumTemp;
				if (nCurID == nID1)
				{
					break;
				}
				if (nCurID != nLastID)
				{
					pBox = this->GetBoxByID(nCurID);
					pBox->m_vecTriangleIdx.push_back(nTriangleIdx);
					nLastID = nCurID;
				}
			}
		}

		glm::vec3 vOffsetPoint3 = rInfo.m_vPoint3 - this->m_vMinPoint;
		u64 nXNum3 = (u64)(vOffsetPoint3.x / this->m_fXStep); if (nXNum3 == this->m_nXStepNum) { nXNum3 -= 1; }
		u64 nYNum3 = (u64)(vOffsetPoint3.y / this->m_fYStep); if (nYNum3 == this->m_nYStepNum) { nYNum3 -= 1; }
		u64 nZNum3 = (u64)(vOffsetPoint3.z / this->m_fZStep); if (nZNum3 == this->m_nZStepNum) { nZNum3 -= 1; }
		u64 nID3 = nXNum3 * 100000000 + nYNum3 * 10000 + nZNum3;
		if (nID3 != nID1 && nID3 != nID2)
		{
			pBox = this->GetBoxByID(nID3);
			pBox->m_vecTriangleIdx.push_back(nTriangleIdx);
		}

		if (nID3 != nID1)
		{
			f32 fDis = glm::distance(rInfo.m_vPoint1, rInfo.m_vPoint3);
			f32 fTempStep = fDis / SUB_STEP_NUM;
			glm::vec3 vDirection = glm::normalize(rInfo.m_vPoint1 - rInfo.m_vPoint3);
			glm::vec3 vLastPoint = rInfo.m_vPoint3;
			u64 nLastID = nID3;
			for (n32 j = 0; j < SUB_STEP_NUM; j++)
			{
				vLastPoint += vDirection * fTempStep;
				glm::vec3 vOffsetPoint = vLastPoint - this->m_vMinPoint;
				u64 nXNumTemp = (u64)(vOffsetPoint.x / this->m_fXStep); if (nXNumTemp == this->m_nXStepNum) { nXNumTemp -= 1; }
				u64 nYNumTemp = (u64)(vOffsetPoint.y / this->m_fYStep); if (nYNumTemp == this->m_nYStepNum) { nYNumTemp -= 1; }
				u64 nZNumTemp = (u64)(vOffsetPoint.z / this->m_fZStep); if (nZNumTemp == this->m_nZStepNum) { nZNumTemp -= 1; }
				u64 nCurID = nXNumTemp * 100000000 + nYNumTemp * 10000 + nZNumTemp;
				if (nCurID == nID1)
				{
					break;
				}
				if (nCurID != nLastID)
				{
					pBox = this->GetBoxByID(nCurID);
					pBox->m_vecTriangleIdx.push_back(nTriangleIdx);
					nLastID = nCurID;
				}
			}
		}

		if (nID3 != nID2)
		{
			f32 fDis = glm::distance(rInfo.m_vPoint2, rInfo.m_vPoint3);
			f32 fTempStep = fDis / SUB_STEP_NUM;
			glm::vec3 vDirection = glm::normalize(rInfo.m_vPoint2 - rInfo.m_vPoint3);
			glm::vec3 vLastPoint = rInfo.m_vPoint3;
			u64 nLastID = nID3;
			for (n32 j = 0; j < SUB_STEP_NUM; j++)
			{
				vLastPoint += vDirection * fTempStep;
				glm::vec3 vOffsetPoint = vLastPoint - this->m_vMinPoint;
				u64 nXNumTemp = (u64)(vOffsetPoint.x / this->m_fXStep); if (nXNumTemp == this->m_nXStepNum) { nXNumTemp -= 1; }
				u64 nYNumTemp = (u64)(vOffsetPoint.y / this->m_fYStep); if (nYNumTemp == this->m_nYStepNum) { nYNumTemp -= 1; }
				u64 nZNumTemp = (u64)(vOffsetPoint.z / this->m_fZStep); if (nZNumTemp == this->m_nZStepNum) { nZNumTemp -= 1; }
				u64 nCurID = nXNumTemp * 100000000 + nYNumTemp * 10000 + nZNumTemp;
				if (nCurID == nID2)
				{
					break;
				}
				if (nCurID != nLastID)
				{
					pBox = this->GetBoxByID(nCurID);
					pBox->m_vecTriangleIdx.push_back(nTriangleIdx);
					nLastID = nCurID;
				}
			}
		}
	}
}