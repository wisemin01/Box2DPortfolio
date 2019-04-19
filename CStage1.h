#pragma once
#include "CScene.h"

class CBox2DEngine;
class CDebugDraw;

class CStage1 :
	public CScene
{
private:
	CBox2DEngine* m_pEngine = nullptr;
	CDebugDraw* m_pDebugDraw = nullptr;
public:
	CStage1();
	~CStage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

