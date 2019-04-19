#pragma once
#include "CSingleton.h"


class CInputManager final:
	public CSingleton<CInputManager>
{
private:

	bool m_CurKeyMap[256];
	bool m_PrevKeyMap[256];

public:
	CInputManager();
	virtual ~CInputManager();

public:

	void KeyMapUpdate();

	bool GetKeyUp	(int _iKey);
	bool GetKeyDown	(int _iKey);
	bool GetKeyPress(int _iKey);

	Vector3 GetScreenMousePos();
	Vector3 GetScrollMousePos();
};

#define INPUTMANAGER CInputManager::GetInst()