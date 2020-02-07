#pragma once

#include<Windows.h>
#include<vector>

using namespace std;

#define MOVEUP 0
#define MOVEDOWN 1
#define MOVERIGHT 2
#define MOVELEFT 3

#define TILEX 33
#define TILEY 25

#define ENEMYBULLET 1
#define PLAYERBULLET 2

class Bullet
{
private:
	POINT position;
	int Dir = -1;

	vector<TCHAR*> m_vAnimationPath;	// 애니메이션 경로
	int m_iAnimationKeyFrame;			// 애니메이션 키 프레임
	int m_iAnimationEndFrame = -1;		// 애니메이션 종료 프레임 -1 일경우에는 애니메이션이 존재 하지 않는다.

	int m_iWidth;
	int m_iHeight;

	int m_SCRWidth;
	int m_SCRHeight;

	TCHAR* m_tDrawPath;
	bool IsDie = false;
	bool IsDestory = false;

	int BulletType = -1;		// 아군 총알 혹은 적군 총알 구분

public:

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
	int GetSCRWidth() { return m_SCRWidth; }
	int GetSCRHeight() { return m_SCRHeight; }
	POINT GetPosition() { return position; }
	bool GetIsDestory() { return IsDestory; }
	bool GetIsDie() { return IsDie; }
	int GetBullet() { return BulletType; }

	void AnimationKeyFrameAdd()
	{
		if (m_iAnimationEndFrame == -1) return;

		m_iAnimationKeyFrame++;

		return;
	}

	TCHAR* GetAnimationPath()
	{
		if (m_iAnimationEndFrame == -1) return m_tDrawPath;

		TCHAR* result = m_vAnimationPath[m_iAnimationKeyFrame];

		AnimationKeyFrameAdd();

		return result;
	}

	Bullet(int DirValue, POINT positionValue,int type)
	{
		Dir = DirValue;
		position = positionValue;
		BulletType = type;

		if (Dir == MOVEUP)
		{
			position.x += 16;
		}
		else if (Dir == MOVEDOWN)
		{
			position.x += 16;
			position.y += 26;
		}
		else if (Dir == MOVELEFT)
		{
			position.y += 13;
		}
		else if (Dir == MOVERIGHT)
		{
			position.x += 33;
			position.y += 13;
		}

		SetBulletImage(Dir);
	}


	void SetBulletImage(int Dir)
	{

		HBITMAP BitMap = NULL;
		BITMAP bit;

		if (Dir == MOVEUP)
		{
			m_tDrawPath = (TCHAR*)TEXT("BattleCity/missile_01.bmp");
			BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/missile_01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);		
		}
		else if (Dir == MOVEDOWN)
		{
			m_tDrawPath = (TCHAR*)TEXT("BattleCity/missile_03.bmp");
			BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/missile_03.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
		else if (Dir == MOVELEFT)
		{
			m_tDrawPath = (TCHAR*)TEXT("BattleCity/missile_02.bmp");
			BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/missile_02.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}
		else if (Dir == MOVERIGHT)
		{
			m_tDrawPath = (TCHAR*)TEXT("BattleCity/missile_00.bmp");
			BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/missile_00.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		}


		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;
	}

	void SetDie()
	{
		if (IsDie) return;

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/explosion_00.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_01.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_02.bmp"));

		m_iAnimationEndFrame = 3;
		m_iAnimationKeyFrame = 0;

		IsDie = true;
	}

	void Update()
	{
		if (IsDestory) return;

		if (IsDie)
		{
			if (m_iAnimationKeyFrame == m_iAnimationEndFrame)
			{
				//
				//	릴리즈 부분 추가.
				//
				IsDestory = true;
			}
		}
		else
		{
			MoveUpdate();
		}	

		
		if (position.x < 0 || position.x > TILEX * 19 || position.y < 0 || position.y > TILEY * 19)
		{
			SetDie();
		}
	}

	void MoveUpdate()
	{
		switch (Dir)
		{
			case MOVEUP:
			{
				MoveYpos(-1);
				break;
			}
			case MOVEDOWN:
			{
				MoveYpos(1);
				break;
			}
			case MOVELEFT:
			{
				MoveXpos(-1);
				break;
			}
			case MOVERIGHT:
			{
				MoveXpos(1);
				break;
			}
		}
	}

	void MoveXpos(int value)
	{
		position.x += value;
	}

	void MoveYpos(int value)
	{
		position.y += value;
	}
};

