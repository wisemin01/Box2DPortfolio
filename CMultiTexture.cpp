#include "DXUT.h"
#include "CMultiTexture.h"
#include "CSingleTexture.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	for (auto iter : vecTexs)
	{
		SAFE_DELETE(iter);
	}
	vecTexs.clear();
}

CTexture * CMultiTexture::AddTexture(const string & _sPath, int _iCnt)
{
	char sz[128] = "";

	for (int i = 1; i <= _iCnt; i++)
	{
		sprintf(sz, _sPath.c_str(), i);

		CTexture* texture = new CSingleTexture;
		texture->AddTexture(sz);
		vecTexs.push_back(texture);
	}

	return this;
}

CTexture * CMultiTexture::GetTexture(int _iCnt)
{
	if (_iCnt == -1)
		return this;
	else
		return vecTexs[_iCnt];
}