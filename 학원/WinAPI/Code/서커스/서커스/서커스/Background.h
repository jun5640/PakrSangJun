#pragma once

#pragma warning(disable: 4996)


#include "CustomObject.h"

class Background : public CustomObject
{
private:
	int reposition_x = 64 * 17;
	int reposition_xmin = 64 * -15;
	int reposition_y = 210;

	int BackGroundType = -1;

	TCHAR* miter = nullptr;
	TCHAR tc[10] = "";
	int m_imiter = 0;
public:

	TCHAR* GetMiter()
	{
		return miter;
	}

	Background(int Type,int xpos,int ypos,TCHAR* TotalMiter = nullptr)
	{
		BITMAP bit = BITMAP();
		HBITMAP BitMap = HBITMAP();

		BackGroundType = Type;

		miter = TotalMiter;

		if (Type == DECO)
		{
			m_IsScroll = true;
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
			m_IsScroll = true;
			m_iType = BACKGROUND;

			m_IsPlayAnimaion = false;

			m_iAnimationKeyFrame = 0;
			m_iAnimationEndFrame = 2;
			m_tDrawPath = (TCHAR*)TEXT("Circus/back_normal.bmp");
			m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/back_normal.bmp"));
			m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/back_normal2.bmp"));


			BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/back_normal.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			FrameTime = 500;
		}
		else if (Type == MITER)
		{
			m_IsScroll = true;
			m_iType = BACKGROUND;

			m_imiter = atoi(miter);

			m_tDrawPath = ((TCHAR*)TEXT("Circus/miter.bmp"));


			BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/miter.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
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

	int GetBackGroundType()
	{
		return BackGroundType;
	}

	virtual void Process() 
	{
		if (BackGroundType != WEED && BackGroundType != MITER)
		{
			if (m_iXpos + m_iWidth < reposition_xmin)
			{
				m_iXpos = reposition_x + (m_iDeltaX % 64);
			}
			else if (m_iXpos >= reposition_x)
			{
				//
				// 조건문 수정필요
				//				
				m_iXpos = reposition_xmin - m_iWidth;

			}
		}

		if (BackGroundType == MITER)
		{
			if (m_iXpos + m_iWidth <= 0)
			{
				if (miter != nullptr)
				{		
					TCHAR * temp = miter;
					m_imiter = atoi(temp);
					m_imiter -= 100;

					if (m_imiter <= 0)
					{
						//m_IsScroll = false;
						return;
					}
					_itoa(m_imiter, tc, 10);
					miter = tc;
						
					m_iXpos = 1000;
				}
			}
			else if (m_iXpos >= 1001)
			{
					
				TCHAR * temp = miter;
				m_imiter = atoi(temp);
				m_imiter += 100;

				if (m_imiter <= 0)
				{
					m_IsScroll = false;
					return;
				}
				_itoa(m_imiter, tc, 10);
				miter = tc;
			
				m_iXpos =0;

			}
		}
		
	};

	int GetiMiter()
	{
		return m_imiter;
	}
};

