#include "DXUT.h"
#include "CStage1.h"

#include "CBox2DEngine.h"
#include "CDebugDraw.h"

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Init()
{
	unsigned int flags = 0;

	flags |= b2Draw::e_shapeBit;
	//flags |= b2Draw::e_jointBit;
	//flags |= b2Draw::e_aabbBit;
	//flags |= b2Draw::e_pairBit;
	//flags |= b2Draw::e_centerOfMassBit;

	m_pEngine = new CBox2DEngine;
	m_pDebugDraw = new CDebugDraw;

	m_pDebugDraw->SetFlags(flags);
	m_pDebugDraw->SetDrawScale(10.0f, 10.0f);
	m_pDebugDraw->SetLineWidth(10);

	m_pEngine->InitBox2DEngine(Vector2(0.0f, 9.8f), Vector2(WINSIZEX / 20, (WINSIZEY - 200) / 10), Vector2(WINSIZEX / 10, 2));
	m_pEngine->SetDebugDraw(m_pDebugDraw);
}

void CStage1::Update()
{
	if (INPUTMANAGER->GetKeyDown(VK_LBUTTON))
	{
		Vector2 vMouse = INPUTMANAGER->GetScrollMousePos();

		m_pEngine->CreateBody(b2BodyType::b2_dynamicBody,
			rand() % 7 + 3, rand() % 7 + 3, vMouse * 0.1f);
	}
	m_pEngine->Step();
}

void CStage1::Render()
{
	m_pEngine->DrawDebugData();

	IMAGEMANAGER->PrintText("BOX2D Tutorial.01\n[ 마우스 왼클릭 : 박스 소환 ]", Vector2(20, 20), 30);
}

void CStage1::Destroy()
{
	SAFE_DELETE(m_pEngine);
	SAFE_DELETE(m_pDebugDraw);
}
