#pragma once
#include "CObject.h"
#include <functional>

class CPopButton :
	public CObject
{
public:
	enum BUTTON_STATE
	{
		NONE,
		ON_MOUSE,
		ON_MOUSEDOWN,
		ON_CLICK
	};
private:

	bool m_bIsAbsolute = false;
	float m_fWidth;
	float m_fHeight;

	std::function<void()> m_pFunc;

public:
	CPopButton(const Vector3& _vPos, const Vector2& _vColSize, CTexture* _texBuns, function<void()> _pFunc);
	virtual ~CPopButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetIsAbsolute(bool _flag) { m_bIsAbsolute = _flag; }
	int  GetButtonState() { return m_eState; }

};

