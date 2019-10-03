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

class T_DLL_EXPORT CMesh
{
public:
	n32 m_nVertexCount;
	SMeshVertex* m_pVertices;	//store the vertices

	n32 m_nTriangelCount;
	SMeshTriangel* m_pTriangels;	//store the triangels

public:
	CMesh();
	~CMesh();
};
