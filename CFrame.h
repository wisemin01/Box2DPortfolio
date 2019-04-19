#pragma once
class CFrame
{
public:
	int m_iCurFrame = 0;
	int m_iFrameStart = 0;
	int m_iFrameEnd = 0;

	unsigned long m_dwFrameSkip = 0;
	unsigned long m_dwFrameDelay = 0;

public:
	CFrame();
	~CFrame();

	void SetFrame(int _iStart, int _iEnd, unsigned long _dwDelay);

	bool Frame();
};

