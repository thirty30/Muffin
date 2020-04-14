#pragma once
#include "TMuffinSysInclude.h"

class CGizmo
{
public:
	GLenum m_eType;
	glm::vec3 m_vColor;
	f32 m_fLineWidth;
	vector<glm::vec3> m_vecPoint;

private:
	void DrawLine();

public:
	CGizmo();
	~CGizmo();
	void Draw();
	void AddPoint(glm::vec3 a_vPoint);
};
