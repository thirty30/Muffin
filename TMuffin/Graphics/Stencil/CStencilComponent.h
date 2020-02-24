#pragma once
#include "TMuffinSysInclude.h"
#include "Component/CComponentBase.h"

class T_DLL_EXPORT CStencilComponent : public CComponentBase
{
public:
	tbool m_bIsStencil;
	GLint m_nDefaultValue;
	GLint m_nTargetValue;
	n32 m_nCondition;
	tbool m_bEnableColor;
	tbool m_bEnableDepth;

	T_SCS
		T_SCP(m_bIsStencil, tbool)
		T_SCP(m_nDefaultValue, GLint)
		T_SCP(m_nTargetValue, GLint)
		T_SCP(m_nCondition, n32)
		T_SCP(m_bEnableColor, tbool)
		T_SCP(m_bEnableDepth, tbool)
	T_SCE


public:
	CStencilComponent() 
	{
		this->m_bIsStencil = false;
		this->m_nDefaultValue = 0;
		this->m_nTargetValue = 0;
		this->m_bEnableColor = true;
		this->m_bEnableDepth = true;
	}
	~CStencilComponent() {}

};