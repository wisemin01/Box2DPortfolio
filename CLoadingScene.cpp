#include "DXUT.h"
#include "CLoadingScene.h"

CLoadingScene::CLoadingScene()
{
}


CLoadingScene::~CLoadingScene()
{
}

void CLoadingScene::Init()
{
	// ================================================
	// 이미지 로드는 이 안에서
	Load("MAIN_BG", "./Resources/MAIN_BACKGROUND.png");
	Load("BUTTON1", "./Resources/UI/Button%d.png", 3);

	Load("CIRCLE", "./Resources/UI/Circle.png");

	Load("STAGE1", "./Resources/STAGE1.png");
	Load("STAGE2", "./Resources/STAGE2.png");
	Load("STAGE3", "./Resources/STAGE3.png");

	// ================================================


	m_iNowLoading = 0;
	m_iLastLoading = m_vecTexPaths.size();
}

void CLoadingScene::Update()
{
	if (m_iNowLoading == m_iLastLoading)
	{
		SCENEMANAGER->ChangeScene("S_MAINMENU");
		return;
	}

	IMAGEMANAGER->AddTexture(m_vecTexPaths[m_iNowLoading].key,
		m_vecTexPaths[m_iNowLoading].path,
		m_vecTexPaths[m_iNowLoading].count);

	m_iNowLoading++;
}

void CLoadingScene::Render()
{
}

void CLoadingScene::Destroy()
{
}
