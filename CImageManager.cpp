#include "DXUT.h"
#include "CImageManager.h"

#include "CSingleTexture.h"
#include "CMultiTexture.h"


CImageManager::CImageManager()
	:m_pSprite(nullptr)
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &m_pSprite);
	m_tBackBufferColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}


CImageManager::~CImageManager()
{
	for (auto iter : m_mapTexs)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapTexs.clear();
	SAFE_RELEASE(m_pSprite);
}

CTexture* CImageManager::AddTexture(const string & _sKey, const string & _sPath, int _iCnt)
{
	auto find = m_mapTexs.find(_sKey);

	if (find == m_mapTexs.end())
	{
		CTexture* texture;

		if (_iCnt == 0)
			texture = new CSingleTexture;
		else
			texture = new CMultiTexture;

		m_mapTexs.insert(make_pair(_sKey, texture->AddTexture(_sPath, _iCnt)));
		return texture;
	}

	return nullptr;
}

CTexture * CImageManager::GetTexture(const string & _sKey, int _iCnt)
{
	auto find = m_mapTexs.find(_sKey);

	if (find != m_mapTexs.end())
		return find->second->GetTexture(_iCnt);
	else
		return nullptr;
}

void CImageManager::Render(CTexture * _pTex, const Vector3 & _vPos, float _fRot, D3DCOLOR _tColor)
{
	if (!_pTex)
		return;

	D3DXMATRIXA16 mat;
	Vector3 vCenter = Vector3(_pTex->tInfo.Width / 2.f, _pTex->tInfo.Height / 2.f, 0);

	D3DXMatrixAffineTransformation2D(&mat, 1.f, NULL, D3DXToRadian(_fRot), &Vector2(_vPos.x, _vPos.y));

	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw(_pTex->pTex, NULL, &vCenter, NULL, _tColor);
}

void CImageManager::ScaleRender(CTexture * _pTex, const Vector3 & _vPos, const Vector3 & _vScale, float _fRot, D3DCOLOR _tColor)
{
	if (!_pTex)
		return;

	D3DXMATRIX mat;
	D3DXMATRIX matScale, matTrans, matRot;
	Vector3 vCenter = Vector3(_pTex->tInfo.Width / 2, _pTex->tInfo.Height / 2, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(_fRot));
	D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, 0);
	D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, _vScale.z);

	mat = matScale * matRot * matTrans;

	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw(_pTex->pTex, nullptr, &vCenter, nullptr, _tColor);
}

void CImageManager::CenterRender(CTexture * _pTex, const Vector3 & _vPos, const Vector3 & _vCenter, float _fRot)
{
	if (!_pTex)
		return;

	D3DXMATRIXA16 mat;
	Vector3 vCenter = Vector3(_pTex->tInfo.Width / 2.f, _pTex->tInfo.Height / 2.f, 0);

	D3DXMatrixAffineTransformation2D(&mat, 1.f, NULL, D3DXToRadian(_fRot), &Vector2(_vPos.x, _vPos.y));

	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw(_pTex->pTex, NULL, &vCenter, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void CImageManager::CropRender(CTexture * _pTex, const Vector3 & _vPos, const RECT & _rcRect, D3DCOLOR _tColor)
{
	if (!_pTex)
		return;

	Vector3 vCenter = Vector3(_pTex->tInfo.Width / 2, _pTex->tInfo.Height / 2, 0);

	m_pSprite->Draw(_pTex->pTex, &_rcRect, &vCenter, nullptr, _tColor);
}

void CImageManager::InfoRender(CTexture * _pTex, const INFO & _tInfo, float _fRot)
{
	if (!_pTex)
		return;

	D3DXMATRIX mat;
	D3DXMATRIX matScale, matTrans, matRot;
	Vector3 vCenter = Vector3(_pTex->tInfo.Width / 2, _pTex->tInfo.Height / 2, 0);

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(_fRot));
	D3DXMatrixTranslation(&matTrans, _tInfo.vPos.x, _tInfo.vPos.y, 0);
	D3DXMatrixScaling(&matScale, _tInfo.vScale.x, _tInfo.vScale.y, _tInfo.vScale.z);

	mat = matScale * matRot * matTrans;

	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw(_pTex->pTex, nullptr, &vCenter, nullptr, _tInfo.tColor);
}

void CImageManager::PrintText(const string & _sText, const Vector2 & _vPos, int _iSize)
{
	LPD3DXFONT lpFont;
	D3DXCreateFont(DXUTGetD3D9Device(), _iSize, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &lpFont);

	D3DXMATRIX mat;
	RECT rc = { 0 };
	D3DXMatrixTranslation(&mat, _vPos.x, _vPos.y, 0);

	m_pSprite->SetTransform(&mat);

	lpFont->DrawTextA(m_pSprite, _sText.c_str(), _sText.size(), &rc, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
	SAFE_RELEASE(lpFont);
}

void CImageManager::OnLostDevice()
{
	m_pSprite->OnLostDevice();
}

void CImageManager::OnResetDevice()
{
	m_pSprite->OnResetDevice();
}

void CImageManager::BeginRender(bool _bIsInterface)
{
	if (_bIsInterface)
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	else
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void CImageManager::EndRender()
{
	m_pSprite->End();
}
