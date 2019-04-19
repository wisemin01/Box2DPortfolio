#pragma once

#include <Box2D/Common/b2Math.h>

class  b2World;
class  b2Body;
class  b2Draw;
struct b2Vec2;
enum   b2BodyType;

class CBox2DEngine
{
private:
	b2World * m_pWorld = nullptr;
public:
	CBox2DEngine();
	~CBox2DEngine();

	void InitBox2DEngine(const b2Vec2& _vGravity,
		const b2Vec2& _vGroundPos, const b2Vec2& _vGroundBoxScale);
	void InitBox2DEngine(const Vector2& _vGravity,
		const Vector2& _vGroundPos, const Vector2& _vGroundBoxScale);

	void Step(float _fTimeStep = 1.0f / 60.0f,
		int32 _iVelocityIterations = 6, int32 _iPositionIterations = 2);

	void DrawDebugData();

	b2World* GetWorld() { return m_pWorld; }

	void SetDebugDraw(b2Draw* _pDebugDraw);

public:

	// 타입 : b2BodyType::
	// 밀도 : density, 마찰 : friction , 반발력 : restitution

	b2Body * CreateBody(b2BodyType _tType, float _fWidth, float _fHeight,
		const Vector2& _vPosition, float _fDensity = 1.0f,
		float _fFriction = 0.3f, float _fRestitution = 0.4f);
	b2Body * CreateBody(b2BodyType _tType, float _fRadius,
		const Vector2& _vPosition, float _fDensity = 1.0f,
		float _fFriction = 0.3f, float _fRestitution = 0.4f);
	b2Body * CreateWall(float _x, float _y, const b2Vec2& _vGroundBoxScale);
};

