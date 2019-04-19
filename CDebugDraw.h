#pragma once

#include <Box2D/Common/b2Draw.h>

class  b2World;

class CDebugDraw : public b2Draw
{
private:
	float m_fLineWidth = 2.0f;

	float m_fDrawScaleX = 1.0f;
	float m_fDrawScaleY = 1.0f;

	float m_fOffsetX = 0.0f;
	float m_fOffsetY = 0.0f;

	bool m_bIsAntialias = false;
public:
	CDebugDraw() {}
	CDebugDraw(RECT *_rcRect, b2World* _pWorld);
	virtual ~CDebugDraw() {}

	virtual void DrawPolygon(const b2Vec2*vertices, int32 vertexCount, const b2Color& color) override;

	virtual void DrawSolidPolygon(const b2Vec2*vertices, int32 vertexCount, const b2Color& color) override;

	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

	virtual void DrawTransform(const b2Transform& xf) {}

	void GetBoundBox2DBounds(RECT *w, b2World *world);

	void SetLineWidth(float _fWidth) { m_fLineWidth = _fWidth; }
	void SetAntialias(bool _bFlag) { m_bIsAntialias = _bFlag; }
	void SetDrawScale(float _fScaleX, float _fScaleY) { m_fDrawScaleX = _fScaleX; m_fDrawScaleY = _fScaleY; }
};