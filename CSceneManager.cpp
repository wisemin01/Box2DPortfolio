#include "DXUT.h"
#include "CSceneManager.h"
#include "CScene.h"

CSceneManager::CSceneManager()
	:m_pCurScene(nullptr),
	m_pNextScene(nullptr)
{
}


CSceneManager::~CSceneManager()
{
	if (m_pCurScene)
		m_pCurScene->Destroy();

	for (auto iter : m_mapScenes)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapScenes.clear();
}

void CSceneManager::AddScene(const string & _sKey, CScene * _pScene)
{
	auto find = m_mapScenes.find(_sKey);

	if (find != m_mapScenes.end())
	{
		MESSAGE_LOG((_sKey + " 씬이 이미 존재합니다.").c_str());
		return;
	}

	m_mapScenes.insert(make_pair(_sKey, _pScene));
}

void CSceneManager::ChangeScene(const string & _sKey)
{
	auto find = m_mapScenes.find(_sKey);

	if (find == m_mapScenes.end())
	{
		MESSAGE_LOG((_sKey + " 씬이 존재하지 않습니다.").c_str());
		return;
	}

	m_pNextScene = find->second;
}

void CSceneManager::UpdateScenes()
{
	if (m_pNextScene)
	{
		if (m_pCurScene)
		{
			m_pCurScene->Destroy();
			OBJMANAGER->ResetAllList();
		}

		m_pCurScene = m_pNextScene;
		m_pNextScene = nullptr;

		m_pCurScene->Init();
	}

	if (m_pCurScene)
		m_pCurScene->Update();

	OBJMANAGER->UpdateObjects();
}

void CSceneManager::RenderScenes()
{
	if (m_pCurScene)
		m_pCurScene->Render();

	OBJMANAGER->RenderObjects();
}
