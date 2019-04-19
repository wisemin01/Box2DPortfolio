#include "DXUT.h"
#include "CStage2.h"

#include "CBox2DEngine.h"
#include "CDebugDraw.h"

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Init()
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

	m_pEngine->CreateWall(WINSIZEX / 20, 1, b2Vec2(WINSIZEX / 10, 2));
	m_pEngine->CreateWall(0, WINSIZEY / 20, b2Vec2(2, WINSIZEY / 10));
	m_pEngine->CreateWall(WINSIZEX / 10, WINSIZEY / 20, b2Vec2(2, WINSIZEY / 10));

	m_pEngine->CreateBody(b2BodyType::b2_dynamicBody, 3, Vector2(WINSIZEX / 2, WINSIZEY / 2) * 0.1f);

}

void CStage2::Update()
{
	if (INPUTMANAGER->GetKeyDown(VK_LBUTTON))
	{
		Vector2 vMouse = INPUTMANAGER->GetScrollMousePos();

		m_pEngine->CreateBody(b2BodyType::b2_dynamicBody, rand() % 3 + 1,
			vMouse * 0.1f, 1.0f, 0.3f, 1.2f);
	}

	m_pEngine->Step();
}

void CStage2::Render()
{
	m_pEngine->DrawDebugData();

	IMAGEMANAGER->PrintText("BOX2D Tutorial.02\n[ 마우스 왼클릭 : 튕기는 공 소환 ]", Vector2(20, 30), 30);
}

void CStage2::Destroy()
{
	SAFE_DELETE(m_pEngine);
	SAFE_DELETE(m_pDebugDraw);
}
