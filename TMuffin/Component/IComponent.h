#pragma once
#include "TMuffinSysInclude.h"

class T_DLL_EXPORT IComponent
{
public:
	virtual ~IComponent() {}
};

class IComponentFactory
{
public:
	virtual ~IComponentFactory() {}

	virtual IComponent* CreateComponent() T_PURE;
};
