#include "CGizmo.h"

CGizmo::CGizmo()
{
	this->m_eType = GL_POINT;
	this->m_vColor = glm::vec3(1, 1, 1);
	this->m_fLineWidth = 1.0f;
	this->m_vecPoint.clear();
}

CGizmo::~CGizmo()
{

}

void CGizmo::DrawLine()
{
	glColor3fv(glm::value_ptr(this->m_vColor));
	glLineWidth(this->m_fLineWidth);
	glBegin(GL_LINES);
	glVertex3fv(glm::value_ptr(this->m_vecPoint[0]));
	glVertex3fv(glm::value_ptr(this->m_vecPoint[1]));
	glEnd();
}

void CGizmo::Draw()
{
	switch (this->m_eType)
	{
	case GL_LINES:
		this->DrawLine();
	default:
		break;
	}
}

void CGizmo::AddPoint(glm::vec3 a_vPoint)
{
	this->m_vecPoint.push_back(a_vPoint);
}
