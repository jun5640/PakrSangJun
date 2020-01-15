#pragma once

#include "CustomObject.h"


class Player : public CustomObject
{

private:

	bool m_IsJump = false;
	bool m_IsLanding = true;
	int m_JumpHeight = 140;
	int m_Ydelta = 0;

public:
	Player(int xpos, int ypos)
	{
		m_iType = PLAYER;
		m_iAnimationKeyFrame = 0;
		m_iAnimationEndFrame = 3;
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/player0.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/player1.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/player2.bmp"));

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/player0.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = xpos;
		m_iYpos = ypos;
		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		FrameTime = 100;
	}

	virtual void Process() 
	{
		if (m_IsJump)
		{
			if (m_Ydelta != m_JumpHeight)
			{
				m_iYpos -= 10;
				m_Ydelta += 10;
			}
			else
			{
				m_IsJump = false;
			}
		}
		else
		{
			if (m_Ydelta == 0)
			{
				m_IsLanding = true;
			}
			else if(m_Ydelta != 0 && !m_IsLanding)
			{
				m_iYpos += 10;
				m_Ydelta -= 10;
			}
		}
	};
	

	void SetJump()
	{
		if (m_IsJump || !m_IsLanding) return;
		m_IsJump = true;
		m_IsLanding = false;
	}

	bool CrashCheck(RECT EnemyRect)
	{
		RECT rect;
		RECT temp = { 0 };

		rect.left = m_iXpos;
		rect.top = m_iYpos;
		rect.right = m_iXpos + m_iWidth;
		rect.bottom = m_iYpos + m_iHeight;

		return IntersectRect(&temp, &rect, &EnemyRect);
	}
};

