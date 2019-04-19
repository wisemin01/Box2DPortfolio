#pragma once
#include "CSingleton.h"

class CScene;

class CSceneManager final:
	public CSingleton<CSceneManager>
{
private:
	map<string, CScene*> m_mapScenes;

	CScene* m_pNextScene;
	CScene* m_pCurScene;

public:
	CSceneManager();
	virtual ~CSceneManager();

public:

	void AddScene(const string& _sKey, CScene* _pScene);
	void ChangeScene(const string& _sKey);

	void UpdateScenes();
	void RenderScenes();

	int GetSceneCount() { return m_mapScenes.size(); }
};

#define SCENEMANAGER CSceneManager::GetInst()