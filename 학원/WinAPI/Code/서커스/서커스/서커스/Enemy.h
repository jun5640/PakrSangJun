#pragma once

#include "CustomObject.h"

class Enemy : public CustomObject
{

private:
	bool m_bReleaseCheck = false;
	int EnemyType;

	void SetEnemy1()
	{

		m_IsScroll = true;
		m_iType = ENEMY;

		m_tDrawPath = ((TCHAR*)TEXT("Circus/enemy.bmp"));

		

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/enemy.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = CREATEENEMYXPOS;
		m_iYpos = CREATEENEMYYPOS;
		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;
	}

	void SetEnemy2()
	{
		m_iType = ENEMY;
		m_iAnimationKeyFrame = 0;
		m_iAnimationEndFrame = 2;
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/front.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/front2.bmp"));

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/front.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = CREATEENEMYXPOS2;
		m_iYpos = CREATEENEMYYPOS2;
		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		FrameTime = 100;
	}

	void SetEnemy3()
	{

		m_IsScroll = true;

		m_iType = ENEMY;

		m_tDrawPath = ((TCHAR*)TEXT("Circus/end.bmp"));

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/end.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = CREATEENEMYXPOS3;
		m_iYpos = CREATEENEMYYPOS3;
		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;
	}

	void SetEnemy4()
	{
		m_IsScroll = true;

		m_iType = ENEMY;
		m_iAnimationKeyFrame = 0;
		m_iAnimationEndFrame = 2;
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/front.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("Circus/front2.bmp"));

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("Circus/front.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iXpos = CREATEENEMYXPOS4;
		m_iYpos = CREATEENEMYYPOS4;
		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRXpos = 0;
		m_SCRYpos = 0;
		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		FrameTime = 100;
	}
public:

	POINT CrashPoint;

	int GetEnemyType() { return EnemyType; }


	void SetData(int Type)
	{
		m_bReleaseCheck = false;
		EnemyType = Type;

		m_iAnimationKeyFrame = 0;
		m_iAnimationEndFrame = -1;
		m_vAnimationPath.clear();

		if (Type == ENEMY1)
		{
			SetEnemy1();
		}
		else if (Type == ENEMY2)
		{
			SetEnemy2();
		}
		else if (Type == ENEMY3)
		{
			SetEnemy3();
		}
		else if (Type == ENEMY4)
		{
			SetEnemy4();
		}
	}


	

	virtual void Process()
	{
		if (m_bReleaseCheck) return;

		if (m_iXpos < -100) m_bReleaseCheck = true;

		if (EnemyType == ENEMY1)
		{
			if (m_ScrollDir == 0)
			{
				m_iXpos -= 10;
			}
			else if (m_ScrollDir < 0)
			{
				m_iXpos -= 15;
			}
			else
			{
				m_iXpos -= 5;
			}		
		}
		
		if (EnemyType == ENEMY3)
		{
			if (m_iXpos <= 900)
			{
				m_IsScroll = false;
			}
		}

		if (EnemyType == ENEMY4)
		{
			if (m_iXpos <= 800)
			{
				m_IsScroll = false;
			}
		}

		CrashPoint.y = CREATEENEMYYPOS + m_iHeight;
		CrashPoint.x = (m_iXpos + m_iXpos + m_iWidth) / 2;
	}

	bool ReleaseCheck()
	{
		return m_bReleaseCheck;
	}
	
	void Release()
	{
		m_bReleaseCheck = true;
	}

	RECT GetCrashRECT()
	{
		RECT rect;

		if (EnemyType == ENEMY1)
		{
			rect.left = CrashPoint.x - 5;
			rect.right = CrashPoint.x + 5;
			rect.top = CrashPoint.y - 5;
			rect.bottom = CrashPoint.y;
		}
		else if (EnemyType == ENEMY2)
		{
			rect.left = m_iXpos;
			rect.top = m_iYpos;
			rect.right = m_iXpos + m_iWidth;
			rect.bottom = m_iYpos + m_iHeight;
		}
		else if (EnemyType == ENEMY3)
		{
			rect.left = m_iXpos;
			rect.top = m_iYpos;
			rect.right = m_iXpos + m_iWidth;
			rect.bottom = m_iYpos + m_iHeight;
		}
		else if (EnemyType == ENEMY4)
		{
			rect.left = m_iXpos;
			rect.top = m_iYpos;
			rect.right = m_iXpos + m_iWidth;
			rect.bottom = m_iYpos + m_iHeight;
		}

		return rect;
	}
};

