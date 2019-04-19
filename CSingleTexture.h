#pragma once
#include "CTexture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

	virtual CTexture* AddTexture(const string& _sPath, int _iCnt = 0) override;
	virtual CTexture* GetTexture(int _iCnt = -1) override;

	virtual int GetLength() { return 1; }
};

