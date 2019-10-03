#pragma once

struct SMeshVertex
{
	f32 X, Y, Z;
	f32 NX, NY, NZ;
	SMeshVertex()
	{
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
		this->NX = 0;
		this->NY = 0;
		this->NZ = 0;
	}
};

struct SMeshTriangel
{
	u32 Vertex1, Vertex2, Vertex3;
	SMeshTriangel()
	{
		this->Vertex1 = 0;
		this->Vertex2 = 0;
		this->Vertex3 = 0;
	}
};

class CMesh
{
private:
	n32 m_nVertexCount;
	SMeshVertex* m_pVertices;	//store the vertices

	n32 m_nTriangelCount;
	SMeshTriangel* m_pTriangels;	//store the triangels

public:
	CMesh();
	~CMesh();

	tbool LoadPlyModel(tstring aFileName);
	n32 GetVertexCount() { return this->m_nVertexCount; }
	n32 GetTriangelCount() { return this->m_nTriangelCount; }
	const SMeshVertex* GetVertex(n32 a_nIndex);
	const SMeshTriangel* GetTriangel(n32 a_nIndex);
};
