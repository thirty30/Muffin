#include "CColliderBox.h"

CColliderBox::CColliderBox() : CColliderBase(E_BOX_COLLIDER)
{
	this->m_vSize = glm::vec3(1.0f, 1.0f, 1.0f);
}

CColliderBox::~CColliderBox()
{

}
