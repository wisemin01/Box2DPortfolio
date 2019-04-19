#include "DXUT.h"
#include "CPopButton.h"



CPopButton::CPopButton(const Vector3 & _vPos, const Vector2 & _vColSize, CTexture * _texBuns, function<void()> _pFunc)
	: m_fWidth(_vColSize.x), m_fHeight(_vColSize.y), m_pFunc(_pFunc)
{
	m_tInfo.vPos = _vPos;
	m_pTexture = _texBuns;
}

CPopButton::~CPopButton()
{
}

void CPopButton::Init()
{
	m_tInfo.vScale = Vector3(0.1f, 0.1f, 0.1f);
	m_tInfo.tColor = D3DCOLOR_XRGB(255, 255, 255);
}

void CPopButton::Update()
{

	// 고정형 UI 라면 고정형 좌표를, 카메라 위치와 관련있다면 Scroll 위치를 가져옴
	Vector3 mousePos = m_bIsAbsolute ? INPUTMANAGER->GetScreenMousePos() : INPUTMANAGER->GetScrollMousePos();

	// 마우스와 충돌 검사할 사각형 설정
	CRECT rc(m_tInfo.vPos.x - m_fWidth / 2.f, m_tInfo.vPos.y - m_fHeight / 2.f,
		m_tInfo.vPos.x + m_fWidth / 2.f, m_tInfo.vPos.y + m_fHeight / 2.f);

	if (Inspection(&rc, &mousePos))
	{
		if (m_eState == NONE || m_eState == ON_CLICK)
			m_eState = ON_MOUSE;
	}
	else if (m_eState == ON_MOUSE)
		m_eState = NONE;


	if (INPUTMANAGER->GetKeyPress(VK_LBUTTON))
	{
		if (Inspection(&rc, &mousePos))
			m_eState = ON_MOUSEDOWN;
		else
			m_eState = NONE;
	}

	if (m_eState == ON_MOUSEDOWN)
	{
		if (INPUTMANAGER->GetKeyUp(VK_LBUTTON)) {
			if (Inspection(&rc, &mousePos)) {
				m_pFunc();
			}
			m_eState = ON_CLICK;
		}
	}

	// 버튼 마우스 오버 효과
	if (m_eState == ON_MOUSE)
		Lerp(&m_tInfo.vScale, m_tInfo.vScale, Vector3(1.1, 1.1, 1.1), (float)(10 * g_fDeltaTime));
	else
		Lerp(&m_tInfo.vScale, m_tInfo.vScale, Vector3(1.0, 1.0, 1.0), (float)(10 * g_fDeltaTime));
}

void CPopButton::Render()
{
	IMAGEMANAGER->ScaleRender(m_pTexture->GetTexture(m_eState == ON_CLICK ? NONE : m_eState), m_tInfo.vPos,
		Vector3(m_tInfo.vScale.x * m_iFlip, m_tInfo.vScale.y, m_tInfo.vScale.z), 0, m_tInfo.tColor);
}

void CPopButton::Destroy()
{
	OBJMANAGER->UnRegisterCollider(this);
}
