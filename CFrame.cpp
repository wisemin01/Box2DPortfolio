#include "DXUT.h"
#include "CFrame.h"


CFrame::CFrame()
{
}


CFrame::~CFrame()
{
}

void CFrame::SetFrame(int _iStart, int _iEnd, unsigned long _dwDelay)
{
	m_iCurFrame = m_iFrameStart = _iStart;
	m_iFrameEnd = _iEnd;

	m_dwFrameDelay = _dwDelay;
	m_dwFrameSkip = GetNowTime();
}

bool CFrame::Frame()
{
	if (m_dwFrameDelay + m_dwFrameSkip < GetNowTime())
	{
		m_dwFrameSkip = timeGetTime();
		if (++m_iCurFrame > m_iFrameEnd)
		{
			m_iCurFrame = m_iFrameStart;
			m_dwFrameSkip = GetNowTime();

			return true;
		}
	}

	return false;
}