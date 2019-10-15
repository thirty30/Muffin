#pragma once

struct SMeshVertex
{
	f32 x, y, z;
	f32 nx, ny, nz;
	SMeshVertex()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->nx = 0;
		this->ny = 0;
		this->nz = 0;
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
