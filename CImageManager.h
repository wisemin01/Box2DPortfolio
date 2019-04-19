#pragma once
#include "CSingleton.h"

#include "CTexture.h"

class CImageManager final:
	public CSingleton<CImageManager>
{
private:
	LPD3DXSPRITE m_pSprite;
	map<string, CTexture*> m_mapTexs;
public:
	D3DCOLOR m_tBackBufferColor;
public:
	CImageManager();
	virtual ~CImageManager();

	CTexture* AddTexture(const string& _sKey, const string& _sPath, int _iCnt = 0);
	CTexture* GetTexture(const string& _sKey, int _iCnt = -1);

public:
	// OBJECT RENDERING FUNC

	void Render(CTexture* _pTex, const Vector3& _vPos,
		float _fRot = 0.f, D3DCOLOR _tColor = D3DCOLOR_XRGB(255, 255, 255));
	void ScaleRender(CTexture* _pTex, const Vector3& _vPos,
		const Vector3& _vScale, float _fRot = 0.f, D3DCOLOR _tColor = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(CTexture* _pTex, const Vector3& _vPos,
		const Vector3& _vCenter, float _fRot = 0.f);
	void CropRender(CTexture* _pTex, const Vector3& _vPos,
		const RECT& _rcRect, D3DCOLOR _tColor = D3DCOLOR_XRGB(255, 255, 255));

	void InfoRender(CTexture* _pTex, const INFO& _tInfo, float _fRot = 0);

	void PrintText(const string& _sText, const Vector2& _vPos, int _iSize);
public:

	void OnLostDevice();
	void OnResetDevice();

	void BeginRender(bool _bIsInterface);
	void EndRender();
	inline void ReBegin(bool _bIsInterface) { EndRender(); BeginRender(_bIsInterface); }
};

#define IMAGEMANAGER CImageManager::GetInst()