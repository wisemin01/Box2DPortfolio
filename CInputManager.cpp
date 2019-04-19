#include "DXUT.h"
#include "CInputManager.h"


CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

void CInputManager::KeyMapUpdate()
{
	memcpy(m_PrevKeyMap, m_CurKeyMap, 256);
	
	for (int i = 0; i < 256; i++)
	{
		if (HIBYTE(GetAsyncKeyState(i)))
			m_CurKeyMap[i] = true;
		else
			m_CurKeyMap[i] = false;
	}
}

bool CInputManager::GetKeyUp(int _iKey)
{
	return (m_CurKeyMap[_iKey] == 0 && m_PrevKeyMap[_iKey] == 1);
}

bool CInputManager::GetKeyDown(int _iKey)
{
	return (m_CurKeyMap[_iKey] == 1 && m_PrevKeyMap[_iKey] == 0);
}

bool CInputManager::GetKeyPress(int _iKey)
{
	return (m_CurKeyMap[_iKey] == 1 && m_PrevKeyMap[_iKey] == 1);
}

Vector3 CInputManager::GetScreenMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	
	Vector3 vMouse = Vector3((float)pt.x, (float)pt.y, 0);

	return vMouse;
}

Vector3 CInputManager::GetScrollMousePos()
{
	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	pt.x = (pt.x - WINSIZEX / 2);
	pt.y = (pt.y - WINSIZEY / 2);

	D3DXVECTOR2 vScroll   = CAMERA->GetCameraPos();
	D3DXVECTOR3 vMousePos = D3DXVECTOR3((float)pt.x + vScroll.x, (float)pt.y + vScroll.y, 0);

	return vMousePos;
}
