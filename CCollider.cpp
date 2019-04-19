#include "DXUT.h"
#include "CCollider.h"

#include "CObject.h"


CCollider::CCollider(CObject* _pObj, const CRECT & _rcCol)
	: m_pOwner(_pObj), m_tCol(_rcCol)
{
}


CCollider::~CCollider()
{

}

const RECT & CCollider::GetCollider()
{
	return m_tCol.GetRect_Global(m_pOwner->GetInfo()->GetPosV2());
}

void CCollider::SetRect(const RECT & _rcCol)
{
	m_tCol = _rcCol;
}

bool CCollider::Inspection(CCollider * col1, CCollider * col2)
{
	RECT rc1 = col1->GetCollider();
	RECT rc2 = col2->GetCollider();
	RECT colRange;

	if (IntersectRect(&colRange, &rc1, &rc2))
		return true;
	else
		return false;
}


CustomRect::CustomRect(long _dwWidth, long _dwHeight)
	: RECT({ -_dwWidth / (long)2, -_dwHeight / (long)2,
		_dwWidth / (long)2, _dwHeight / (long)2 })
{
}

CustomRect::CustomRect(long _dwLeft, long _dwTop, long _dwRight, long _dwBottom)
	: RECT({ _dwLeft, _dwTop, _dwRight, _dwBottom })
{
}

const RECT & CustomRect::GetRect_Global(const Vector2 & _vPos)
{
	return RECT({ left + (long)_vPos.x,
	top + (long)_vPos.y,
	right + (long)_vPos.x,
	bottom + (long)_vPos.y });
}