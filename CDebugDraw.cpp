#include "DXUT.h"
#include "CDebugDraw.h"

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

CDebugDraw::CDebugDraw(RECT * _rcRect, b2World * _pWorld)
{
	RECT rt;
	GetBoundBox2DBounds(&rt, _pWorld);

	m_fDrawScaleX = (_rcRect->right - _rcRect->left) / (abs(rt.right) + abs(rt.left));
	m_fDrawScaleY = (_rcRect->bottom - _rcRect->top) / (abs(rt.bottom) + abs(rt.top));

	m_fOffsetX = ((_rcRect->right - _rcRect->left) / 2) - ((abs(rt.right + rt.left)) / 2 * m_fDrawScaleX)
		+ (abs(rt.right) * m_fDrawScaleX);
	m_fOffsetY = ((_rcRect->bottom - _rcRect->top) / 2) - ((abs(rt.top + rt.bottom)) / 2 * m_fDrawScaleY)
		+ (abs(rt.bottom) * m_fDrawScaleY);
}

void CDebugDraw::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	ID3DXLine* ILine;
	Vector2 *vecList = new Vector2[vertexCount + 1];

	for (int i = 0; i < vertexCount; i++)
		vecList[i] = Vector2(vertices[i].x * m_fDrawScaleX, vertices[i].y * m_fDrawScaleY);

	vecList[vertexCount] = Vector2(vertices[0].x * m_fDrawScaleX, vertices[0].y * m_fDrawScaleY);

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	ILine->SetWidth(m_fLineWidth);
	ILine->SetAntialias(m_bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, vertexCount + 1, D3DCOLOR_XRGB((DWORD)color.r * 255, (DWORD)color.g * 255, (DWORD)color.b * 255));

	ILine->End();
	SAFE_RELEASE(ILine);
	SAFE_DELETE_ARRAY(vecList);
}

void CDebugDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	// ¹Ì±¸Çö
	DrawPolygon(vertices, vertexCount, color);
}

void CDebugDraw::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{
	CTexture* text = IMAGEMANAGER->GetTexture("CIRCLE");

	IMAGEMANAGER->ScaleRender(text, Vector3(center.x * m_fDrawScaleX, center.y * m_fDrawScaleY, 0), Vector3(0.425, 0.425, 0.425) * radius, 0,
		D3DCOLOR_XRGB((DWORD)color.r * 255, (DWORD)color.g * 255, (DWORD)color.b * 255));
}

void CDebugDraw::DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color)
{
	DrawCircle(center, radius, color);
}

void CDebugDraw::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	ID3DXLine* ILine;
	Vector2 vecList[2];

	vecList[0] = Vector2(p1.x, p1.y);
	vecList[1] = Vector2(p2.x, p2.y);

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	ILine->SetWidth(m_fLineWidth);
	ILine->SetAntialias(m_bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, 2, D3DCOLOR_XRGB((DWORD)color.r * 255, (DWORD)color.g * 255, (DWORD)color.b * 255));

	ILine->End();
	SAFE_RELEASE(ILine);
}

void CDebugDraw::GetBoundBox2DBounds(RECT * w, b2World * world)
{
	b2Body *b;
	b2Fixture* fix;
	b2AABB bound;
	float minX, maxX, minY, maxY;

	minX = minY = 1000000.0;
	maxX = maxY = -1000000.0;

	b = world->GetBodyList();
	while (b)
	{
		fix = b->GetFixtureList();
		while (fix)
		{
			bound = fix->GetAABB(0);

			if (bound.lowerBound.x < minX)
				minX = bound.lowerBound.x;
			if (bound.upperBound.x > maxX)
				maxX = bound.upperBound.x;
			if (bound.lowerBound.y < minY)
				minY = bound.lowerBound.y;
			if (bound.upperBound.y > maxY)
				maxY = bound.upperBound.y;

			fix = fix->GetNext();
		}
		b = b->GetNext();
	}

	maxX += 2.0;
	maxY += 2.0;
	minX -= 2.0;
	minY -= 2.0;

	w->left = (long)minX;
	w->right = (long)maxX;
	w->bottom = (long)minY;
	w->top = (long)maxY;
}
