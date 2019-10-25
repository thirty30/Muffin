#pragma once

struct SMeshVertex
{
	f32 x, y, z;
	f32 nx, ny, nz;
	f32 u0, v0;
	f32 u1, v1;
	SMeshVertex()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->nx = 0;
		this->ny = 0;
		this->nz = 0;
		this->u0 = 0;
		this->v0 = 0;
		this->u1 = 0;
		this->v1 = 0;
	}
};

struct SMeshTriangle
{
	u32 Vertex1, Vertex2, Vertex3;
	SMeshTriangle()
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

	n32 m_nTriangleCount;
	SMeshTriangle* m_pTriangles;	//store the triangels

public:
	CMesh();
	~CMesh();
};
