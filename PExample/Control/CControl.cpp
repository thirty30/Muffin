#include "stdafx.h"

void ControlKeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	CGame::GetSingleton().GetControlManager()->KeyEvent(a_nKey, a_nScancode, a_nAction, a_nMods);
}

void ControlMouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	CGame::GetSingleton().GetControlManager()->MouseEvent(a_nKey, a_nAction, a_nMods);
}

void ControlCursorEvent(f64 a_fX, f64 a_fY)
{
	CGame::GetSingleton().GetControlManager()->CursorEvent(a_fX, a_fY);
}

void ControlScrollEvent(f64 a_fX, f64 a_fY)
{
	CGame::GetSingleton().GetControlManager()->ScrollEvent(a_fX, a_fY);
}


CControlManager::CControlManager()
{
	this->m_vecControls.clear();
}

CControlManager::~CControlManager()
{
	for (n32 i = 0; i < this->m_vecControls.size(); i++)
	{
		delete this->m_vecControls[i];
	}
	this->m_vecControls.clear();
}

void CControlManager::KeyEvent(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods)
{
	for (n32 i = 0; i < this->m_vecControls.size(); i++)
	{
		this->m_vecControls[i]->KeyEvent(a_nKey, a_nScancode, a_nAction, a_nMods);
	}
}

void CControlManager::MouseEvent(n32 a_nKey, n32 a_nAction, n32 a_nMods)
{
	for (n32 i = 0; i < this->m_vecControls.size(); i++)
	{
		this->m_vecControls[i]->MouseEvent(a_nKey, a_nAction, a_nMods);
	}
}

void CControlManager::CursorEvent(f64 a_fX, f64 a_fY)
{
	for (n32 i = 0; i < this->m_vecControls.size(); i++)
	{
		this->m_vecControls[i]->CursorEvent(a_fX, a_fY);
	}
}

void CControlManager::ScrollEvent(f64 a_fX, f64 a_fY)
{
	for (n32 i = 0; i < this->m_vecControls.size(); i++)
	{
		this->m_vecControls[i]->ScrollEvent(a_fX, a_fY);
	}
}
