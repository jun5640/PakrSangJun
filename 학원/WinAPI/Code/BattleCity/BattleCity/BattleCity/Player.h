#pragma once

#include "BasePlayer.h"
#include "Bullet.h"

#define MOVEUP 0
#define MOVEDOWN 1
#define MOVERIGHT 2
#define MOVELEFT 3

#define ENEMYBULLET 1
#define PLAYERBULLET 2


class Player : public BasePlayer
{
private:
	int Dir = 1;
	int PreDir = -1;

	Bullet * pBullet = nullptr;
public:
	~Player()
	{
		delete pBullet;
	}
	Player(POINT createPosition)
	{
		position = createPosition;

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/tank_left_00.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		SetUp();
	}

	void InputKeyUpdate()
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			Dir = MOVEUP;
			return;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			Dir = MOVEDOWN;
			return;
		}

		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			Dir = MOVERIGHT;
			return;
		}

		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			Dir = MOVELEFT;
			return;
		}

		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			Fire();
			return;
		}

		Dir = -1;

	}

	Bullet* GetBullet()
	{
		return pBullet;
	}

	void BulletRelease()
	{
		delete pBullet;
		pBullet = nullptr;
	}

	virtual void Fire()
	{
		if (pBullet == nullptr)
		{
			pBullet = new Bullet(PreDir, position, PLAYERBULLET);
		}
	}

	void PlayerMoveUpdate()
	{
		switch (Dir)
		{
			case MOVEUP:
			{
				if (Dir != PreDir)
				{
					PreDir = Dir;
					SetUp();
				}
				MoveYpos(-1);
				break;
			}
			case MOVEDOWN:
			{
				if (Dir != PreDir)
				{
					PreDir = Dir;
					SetDown();
				}
				MoveYpos(1);
				break;
			}
			case MOVELEFT:
			{
				if (Dir != PreDir)
				{
					PreDir = Dir;
					SetLeft();
				}
				MoveXpos(-1);
				break;
			}
			case MOVERIGHT:
			{
				if (Dir != PreDir)
				{
					PreDir = Dir;
					SetRight();
				}
				MoveXpos(1);
				break;
			}
		}
	}

	void MoveCancle()
	{
		switch (Dir)
		{
			case MOVEUP:
			{
				MoveYpos(1);
				break;
			}
			case MOVEDOWN:
			{
				MoveYpos(-1);
				break;
			}
			case MOVELEFT:
			{
				MoveXpos(1);
				break;
			}
			case MOVERIGHT:
			{
				MoveXpos(-1);
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

	void SetLeft()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_left_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_left_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetRight()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_right_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_right_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetUp()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_up_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_up_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetDown()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_down_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/tank_down_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}
};

