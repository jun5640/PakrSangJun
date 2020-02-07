#pragma once

#include "BasePlayer.h"
#include "Bullet.h"
#include "CommonFeature.h"
#include "Astar.h"
#include "Astart2.h"

#define MOVEUP 0
#define MOVEDOWN 1
#define MOVERIGHT 2
#define MOVELEFT 3

#define ENEMYBULLET 1
#define PLAYERBULLET 2


class EnemyPlayer : public BasePlayer
{
private:
	int Dir = 1;
	int PreDir = -1;

	int row;
	int col;

	int targetRow;
	int targetCol;

	

	Astar PathFind;
	//Astar2 PathFind2;

	Bullet * pBullet = nullptr;
public:

	~EnemyPlayer()
	{
		delete pBullet;
	}
	EnemyPlayer(POINT createPosition,int rowvalue,int colvalue,int TargetRow,int TargetCol, MapToolTile tileary[19][19])
	{
		row = rowvalue;
		col = colvalue;

		targetRow = TargetRow;
		targetCol = TargetCol;

		position = createPosition;

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, TEXT("BattleCity/e_left_00.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_iWidth = bit.bmWidth;
		m_iHeight = bit.bmHeight;

		m_SCRWidth = bit.bmWidth;
		m_SCRHeight = bit.bmHeight;

		SetUp();

		PathFind.SetPath(row, col, TargetRow, TargetCol, tileary);
		//PathFind2.SetPath(row, col, TargetRow, TargetCol, tileary);
	}

	void Process()
	{
		POINT getpoint = PathFind.GetPoint();
		Dir = PathFind.GetDir();
		Animationupdate(Dir);

		if (getpoint.x == -1 && getpoint.y == -1)
		{
			Fire();
			return;
		}

		if (getpoint.x == position.x && getpoint.y == position.y)
		{
			PathFind.erasepath(position);
			return;
		}

		if (getpoint.x > position.x)
		{
			position.x = position.x + 1;
		}
		else if (getpoint.x < position.x)
		{
			position.x = position.x - 1;
		}

		if (getpoint.y > position.y)
		{
			position.y = position.y + 1;
		}
		else if (getpoint.y < position.y)
		{
			position.y = position.y - 1;
		}

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
			pBullet = new Bullet(PreDir, position,ENEMYBULLET);
		}
	}

	void Animationupdate(int dir)
	{
		if (PreDir != Dir && Dir != -100)
		{
			PreDir = Dir;
		}
		else
		{
			return;
		}

		switch (dir)
		{
			case MOVEUP:
			{
				SetUp();
				break;
			}
			case MOVEDOWN:
			{

				SetDown();
				break;
			}
			case MOVELEFT:
			{

				SetLeft();
				break;
			}
			case MOVERIGHT:
			{
				SetRight();
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

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_left_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_left_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetRight()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_right_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_right_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetUp()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_up_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_up_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}

	void SetDown()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_down_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/e_down_01.bmp"));

		m_iAnimationEndFrame = 2;
		m_iAnimationKeyFrame = 0;
	}
};

