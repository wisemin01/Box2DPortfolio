#include "DXUT.h"
#include "CBox2DEngine.h"

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#pragma comment(lib,"Box2D\\Box2D.lib")


CBox2DEngine::CBox2DEngine()
{
}


CBox2DEngine::~CBox2DEngine()
{
	SAFE_DELETE(m_pWorld);
}

void CBox2DEngine::InitBox2DEngine(const b2Vec2 & _vGravity, const b2Vec2 & _vGroundPos, const b2Vec2 & _vGroundBoxScale)
{
	if (m_pWorld)
	{
		MESSAGE_LOG("이미 월드가 존재합니다.");
		return;
	}

	m_pWorld = new b2World(_vGravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(_vGroundPos.x, _vGroundPos.y);

	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(_vGroundBoxScale.x, _vGroundBoxScale.y);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void CBox2DEngine::InitBox2DEngine(const Vector2 & _vGravity, const Vector2 & _vGroundPos, const Vector2 & _vGroundBoxScale)
{
	if (m_pWorld)
	{
		MESSAGE_LOG("이미 월드가 존재합니다.");
		return;
	}

	m_pWorld = new b2World(b2Vec2(_vGravity.x, _vGravity.y));

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(_vGroundPos.x, _vGroundPos.y);

	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(_vGroundBoxScale.x, _vGroundBoxScale.y);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void CBox2DEngine::Step(float _fTimeStep, int32 _iVelocityIterations, int32 _iPositionIterations)
{
	m_pWorld->Step(_fTimeStep, _iVelocityIterations, _iPositionIterations);
}

void CBox2DEngine::DrawDebugData()
{
	m_pWorld->DrawDebugData();
}

void CBox2DEngine::SetDebugDraw(b2Draw * _pDebugDraw)
{
	m_pWorld->SetDebugDraw(_pDebugDraw);
}

b2Body * CBox2DEngine::CreateBody(b2BodyType _tType, float _fWidth, float _fHeight, const Vector2 & _vPosition,
	float _fDensity, float _fFriction, float _fRestitution)
{
	b2BodyDef bodyDef;
	bodyDef.type = _tType;
	bodyDef.position.Set(_vPosition.x, _vPosition.y);
	b2Body* body = m_pWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_fWidth, _fHeight);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = _fDensity;
	fixtureDef.friction = _fFriction;
	fixtureDef.restitution = _fRestitution;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body * CBox2DEngine::CreateBody(b2BodyType _tType, float _fRadius,
	const Vector2 & _vPosition, float _fDensity, float _fFriction, float _fRestitution)
{
	b2BodyDef bodyDef;
	bodyDef.type = _tType;
	bodyDef.position.Set(_vPosition.x, _vPosition.y);
	b2Body* body = m_pWorld->CreateBody(&bodyDef);

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = _fRadius;
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;

	fixtureDef.density = _fDensity;
	fixtureDef.friction = _fFriction;
	fixtureDef.restitution = _fRestitution;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body * CBox2DEngine::CreateWall(float _x, float _y, const b2Vec2 & _vGroundBoxScale)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(_x, _y);

	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(_vGroundBoxScale.x, _vGroundBoxScale.y);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	return groundBody;
}
