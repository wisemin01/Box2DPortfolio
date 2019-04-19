#pragma once
class CTexture
{
public:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXIMAGE_INFO tInfo;
public:
	CTexture();
	virtual ~CTexture();

	virtual CTexture* AddTexture(const string& _sPath, int _iCnt = 0) PURE;
	virtual CTexture* GetTexture(int _iCnt = -1) PURE;

	virtual int GetLength() PURE;
};

