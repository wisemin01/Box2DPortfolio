#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

	void OnInit();
	void OnUpdate();
	void OnRender();
	void OnDestroy();

	void OnLostDevice();
	void OnResetDevice();

	LRESULT CALLBACK OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

