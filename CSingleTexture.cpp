#include "DXUT.h"
#include "CSingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	SAFE_RELEASE(pTex);
}

CTexture * CSingleTexture::AddTexture(const string & _sPath, int _iCnt)
{
	D3DXGetImageInfoFromFileA(_sPath.c_str(), &tInfo);

	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), _sPath.c_str(), tInfo.Width, tInfo.Height, tInfo.MipLevels, 0, tInfo.Format,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(10, 10, 10, 10), &tInfo, 0, &pTex);

	return this;
}

CTexture * CSingleTexture::GetTexture(int _iCnt)
{
	return this;
}
