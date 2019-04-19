#include "DXUT.h"
#include "CMainMenu.h"

#include "CPopButton.h"

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
}

void CMainMenu::Init()
{
	m_pBackground = IMAGEMANAGER->GetTexture("MAIN_BG");

	// 오른쪽 버튼
	OBJMANAGER->Insert(CObjManager::UI,
		new CPopButton(Vector3(WINSIZEX / 2 + 500, WINSIZEY - 380, 0), Vector2(120, 120),
			IMAGEMANAGER->GetTexture("BUTTON1"),
			[&]() {
				m_iCurSceneCount++;
				if (m_iCurSceneCount > m_iMaxSceneCount)
					m_iCurSceneCount = 0;
			}))->SetFlip(1);
	// 왼쪽 버튼
	OBJMANAGER->Insert(CObjManager::UI,
		new CPopButton(Vector3(WINSIZEX / 2 - 500, WINSIZEY - 380, 0), Vector2(120, 120),
			IMAGEMANAGER->GetTexture("BUTTON1"),
			[&]() {
				m_iCurSceneCount--;
				if (m_iCurSceneCount < 0)
					m_iCurSceneCount = m_iMaxSceneCount;
			}))->SetFlip(-1);

	CAMERA->SetCamera(v2Center);

	m_iCurSceneCount = 0;
	m_iMaxSceneCount = SCENEMANAGER->GetSceneCount() - 2;
}

void CMainMenu::Update()
{
	CRECT crc(576, 324);

	if (Inspection(&crc.GetRect_Global(v2Center + Vector2(0, 200)), &INPUTMANAGER->GetScreenMousePos()))
	{
		if (INPUTMANAGER->GetKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->ChangeScene("S_STAGE" + to_string(m_iCurSceneCount + 1));
		}
	}

	if (INPUTMANAGER->GetKeyDown(VK_ESCAPE)) PostQuitMessage( NULL );
}

void CMainMenu::Render()
{
	IMAGEMANAGER->Render(m_pBackground, v3Center, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	IMAGEMANAGER->ScaleRender(IMAGEMANAGER->GetTexture("STAGE" + to_string(m_iCurSceneCount + 1)), v3Center + Vector3(0, 200, 0),
		Vector3(0.3, 0.3, 0.3));
}

void CMainMenu::Destroy()
{
}
