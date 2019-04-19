#pragma once
#include "CTexture.h"

class CSingleTexture;

class CMultiTexture :
	public CTexture
{
private:
	vector<CTexture*> vecTexs;
public:
	CMultiTexture();
	virtual ~CMultiTexture();
public:

	virtual CTexture* AddTexture(const string& _sPath, int _iCnt = 0);
	virtual CTexture* GetTexture(int _iCnt = -1);

	virtual int GetLength() { return vecTexs.size(); }
};

