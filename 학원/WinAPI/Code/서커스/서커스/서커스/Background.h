#pragma once

#include "CustomObject.h"

class Background : public CustomObject
{
public:
	Background(int Type,int xpos,int ypos)
	{
		BITMAP bit = BITMAP();
		HBITMAP BitMap = HBITMAP();

		if (Type == DECO)
		{
			m_iType = BACKGROUND;

			m_tDrawPath = ((TCHAR*)TEXT("Circus/back_deco.bmp"));


			BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/back_deco.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);		
		}
		else if (Type == WEED)
		{
			m_iType = BACKGROUND;

			m_tDrawPath = ((TCHAR*)TEXT("Circus/back.bmp"));


			BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/back.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
		else if (Type == HUMAN)
		{
			m_iType = BACKGROUND;

			m_iAnimationKeyFrame = 0;
			m_iAnimationEndFrame = 2;
			m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/back_normal.bmp"));
			m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/back_normal2.bmp"));


			BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/back_normal.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			FrameTime = 500;
		}

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = xpos;
		m_iYpos = ypos;

		if (Type == WEED)
		{
			m_iWidth = 1024;
			m_iHeight = 500;
		}
		else
		{
			m_iWidth = bit.bmWidth;
			m_iHeight = bit.bmHeight;
		}

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;
	}

	virtual void Process() {};
};

