#pragma once
#include "CScene.h"
class CMainMenu :
	public CScene
{
private:
	CTexture * m_pBackground;
	
	int m_iMaxSceneCount;
	int m_iCurSceneCount;
public:
	CMainMenu();
	virtual ~CMainMenu();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

