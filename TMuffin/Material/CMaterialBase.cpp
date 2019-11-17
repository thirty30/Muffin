#include "pch.h"


CMaterialBase::CMaterialBase()
{
	this->m_nShaderProgramID = 0;
}

CMaterialBase::~CMaterialBase()
{

}

T_INLINE void CMaterialBase::SetShaderProgramID(n32 a_nShaderProgramID)
{
	this->m_nShaderProgramID = a_nShaderProgramID;
}

T_INLINE n32 CMaterialBase::GetShaderProgramID()
{
	return this->m_nShaderProgramID;
}
