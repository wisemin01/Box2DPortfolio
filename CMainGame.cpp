#include "DXUT.h"
#include "CMainGame.h"

#include "CLoadingScene.h"
#include "CMainMenu.h"


#include "CStage1.h"
#include "CStage2.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

void CMainGame::OnInit()
{
	SCENEMANAGER->AddScene("S_LOADING", new CLoadingScene);
	SCENEMANAGER->AddScene("S_MAINMENU" , new CMainMenu);
	SCENEMANAGER->AddScene("S_STAGE1", new CStage1);
	SCENEMANAGER->AddScene("S_STAGE2", new CStage2);

	SCENEMANAGER->ChangeScene("S_LOADING");

	CAMERA->SetCamera(Vector2(WINSIZEX / 2, WINSIZEY / 2));
}

void CMainGame::OnUpdate()
{
	INPUTMANAGER->KeyMapUpdate();
	SCENEMANAGER->UpdateScenes();

	CAMERA->Update();

	if (INPUTMANAGER->GetKeyDown(VK_ESCAPE)) SCENEMANAGER->ChangeScene("S_MAINMENU");
}

void CMainGame::OnRender()
{
	CAMERA->SetTransform();

	IMAGEMANAGER->BeginRender(false);

	SCENEMANAGER->RenderScenes();

	IMAGEMANAGER->EndRender();
}

void CMainGame::OnDestroy()
{
	CSceneManager::DestroyInst();
	CObjManager::DestroyInst();
	CImageManager::DestroyInst();
	CInputManager::DestroyInst();
	CCameraManager::DestroyInst();
}

void CMainGame::OnLostDevice()
{
	IMAGEMANAGER->OnLostDevice();
}

void CMainGame::OnResetDevice()
{
	IMAGEMANAGER->OnResetDevice();
}

HRESULT CMainGame::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
