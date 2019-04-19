#pragma once

class CObject;

typedef struct CustomRect : public RECT
{
public:
	CustomRect() : RECT({ 0,0,0,0 }) {}
	CustomRect(const RECT& _rcRect) : RECT(_rcRect) {}
	CustomRect(long _dwWidth, long _dwHeight);
	CustomRect(long _dwLeft, long _dwTop,
		long _dwRight, long _dwBottom);

	const RECT& GetRect_Global(const Vector2& _vPos);
} CRECT;

class CCollider
{
private:
	CObject * m_pOwner;

	CRECT	m_tCol;
public:
	CCollider(CObject* _pObj) : m_pOwner(_pObj) {}
	CCollider(CObject* _pObj, const CRECT& _rcCol);
	CCollider(CObject* _pObj, bool _bIsStatic) : m_pOwner(_pObj) {}
	virtual ~CCollider();

	const RECT& GetCollider();

	void SetRect(const RECT& _rcCol);

	inline void SetOwner(CObject* _pObj) { m_pOwner = _pObj; }
	inline CObject* GetOwner() { return m_pOwner; }

public:
	static bool Inspection(CCollider* col1, CCollider* col2);
};

