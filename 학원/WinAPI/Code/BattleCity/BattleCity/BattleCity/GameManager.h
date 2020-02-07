#pragma once

#include "SingletonBase.h"
#include "FileManager.h"
#include "DrawManager.h"
#include "Player.h"
#include "BasePlayer.h"
#include "EnemyPlayer.h"
#include <time.h>

#define ENEMYBULLET 1
#define PLAYERBULLET 2

#define MENU   0
#define GAME   1
#define CLEAR   2
#define END     3


class GameManager : public SingletonBase<GameManager>
{
private:

	MapToolTile TileInfos[19][19];
	bool IsLoad = false;

	Player* player;
	vector<EnemyPlayer*> vEnemyPlayer;

	int LifeRow;
	int LifeCol;

	int SceneState = MENU;


	int EnemyCreateTime = 5000;
	int EnemyCreatePreTime = 0;


	int EnemyCount = 1;

	LPCSTR PATH[5] = { "Save.txt","Save2.txt" ,"Save3.txt" ,"Save4.txt" ,"Save5.txt" };

	int STAGE = 10;
	HWND g_hWnd = nullptr;
public:

	void InIt()
	{
		POINT point;
		EnemyCreateTime = 5000;
		EnemyCreatePreTime = 0;
		EnemyCount = 10;

		if (vEnemyPlayer.size() != 0) EnemyRelese();
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				point.x = TILEX * i;
				point.y = TILEY * j;

				TileInfos[i][j].position = point;
				TileInfos[i][j].IsSet = false;
			}
		}
	}

	void EnemyRelese()
	{
		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end();iter++)
		{
				delete (*iter);
		}
		vEnemyPlayer.clear();
	}

	void Load(HWND hWnd)
	{
		if(g_hWnd == nullptr)g_hWnd = hWnd;
		FileManager::Instance()->Load(hWnd, TileInfos, PATH[STAGE]);
		IsLoad = true;
		POINT point;
		point.x = 300;
		point.y = 300;
		if (player != nullptr)
		{
			delete player;
			player = nullptr;
		}

		player = new Player(point);

	

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{	
				if (!_tcscmp(TileInfos[i][j].tileinfo.GetImagePath(),(TCHAR*)TEXT("BattleCity/block13.bmp")))
				{
					TileInfos[i][j].tileinfo.SetIsLife(true);
					LifeRow = i;
					LifeCol = j;
				}
			}
		}
	}

	void CreateEnemy()
	{
		if (EnemyCount <= 0) return;

		srand((unsigned int)time(NULL));
		int value = rand() % 2;

		int cur = clock();

		if (cur - EnemyCreatePreTime > EnemyCreateTime)
		{
			if (value == 0)
			{
				EnemyPlayer* add = new EnemyPlayer(TileInfos[1][1].position, 1, 1, LifeRow, LifeCol, TileInfos);
				vEnemyPlayer.push_back(add);
			}
			else
			{

				EnemyPlayer* add = new EnemyPlayer(TileInfos[17][1].position, 17, 1, LifeRow, LifeCol, TileInfos);
				vEnemyPlayer.push_back(add);
			}
			EnemyCreatePreTime = cur;
			EnemyCreateTime = rand() % 5000 + 3000;
			EnemyCount--;
		}
	}

	void UnLoad()
	{
		IsLoad = false;
	}

	void Update(HDC hdc)
	{
		if (!IsLoad) return;
		
		switch (SceneState)
		{
			case MENU:
				MenuUpdate(hdc);
				break;
			case GAME:
				GameUpdate(hdc);
				break;
			case END:
				ENDUpdate(hdc);
				break;
			case CLEAR:
				CLEARUpdate(hdc);
				break;
		}
	}

	void MenuUpdate(HDC hdc)
	{
		DrawManager::Instance()->InitCanvas(hdc);
		DrawManager::Instance()->DrawUITEXT(260, 200, (TCHAR*)TEXT("Battle City"), 11);
		DrawManager::Instance()->DrawUITEXT(260, 300, (TCHAR*)TEXT("PressEnter"), 10);
		DrawManager::Instance()->DrawCanvas(hdc);

		MenuKeyDownUpdate();
	}

	void ENDUpdate(HDC hdc)
	{
		DrawManager::Instance()->InitCanvas(hdc);
		DrawManager::Instance()->DrawUITEXT(260, 200, (TCHAR*)TEXT("GAMEOVER"), 7);
		DrawManager::Instance()->DrawUITEXT(260, 300, (TCHAR*)TEXT("PressBACKSPACE"), 14);
		DrawManager::Instance()->DrawCanvas(hdc);

		MenuKeyDownUpdate();
	}

	void CLEARUpdate(HDC hdc)
	{
		DrawManager::Instance()->InitCanvas(hdc);
		DrawManager::Instance()->DrawUITEXT(260, 200, (TCHAR*)TEXT("CLEAR"), 5);
		DrawManager::Instance()->DrawUITEXT(260, 300, (TCHAR*)TEXT("PressBACKSPACE"), 14);
		DrawManager::Instance()->DrawCanvas(hdc);

		MenuKeyDownUpdate();
	}

	void GameUpdate(HDC hdc)
	{
		DrawManager::Instance()->InitCanvas(hdc);
		DrawFloor();
		DrawBullet();
		DrawPlayer();
		DrawBmp();
		DrawManager::Instance()->DrawGray(hdc);
		DrawRemainEnemyUI();
		DrawManager::Instance()->DrawCanvas(hdc);

		BulletUpdate();
		player->InputKeyUpdate();
		player->PlayerMoveUpdate();
		PlayerCrushCheck();
		BulletCrushCheck();
		BulletReleaseCheck();
		EnemyPocess();
		CreateEnemy();
		GameClearCheck();
	}

	void DrawRemainEnemyUI()
	{
		//TEXT("BattleCity/white.bmp")
		for (int i = 0; i < EnemyCount; i++)
		{
			DrawManager::Instance()->DrawUIBmp((TCHAR*)TEXT("BattleCity/enemy_icon.bmp"), TILEX * 19 + 20, 13 * i, 14, 12);
		}
	}
	
	void GameClearCheck()
	{
		if (vEnemyPlayer.size() == 0 && EnemyCount == 0)
		{
			SceneState = CLEAR;
		}
	}
	void MenuKeyDownUpdate()
	{
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			if (SceneState == MENU)
			{
				InIt();
				Load(g_hWnd);
				SceneState = GAME;
			}
			return;
		}

		if (GetKeyState(VK_BACK) & 0x8000)
		{
			if (SceneState == END)
			{
				SceneState = MENU;
				STAGE = 0;
			}
			else if (SceneState == CLEAR)
			{
				if (STAGE != 4)
				{
					STAGE++;
					InIt();
					Load(g_hWnd);
					SceneState = GAME;
				}
				else
				{
					SceneState = MENU;
					STAGE = 0;
				}
			}
			return;
		}
	}

	void EnemyPocess()
	{
		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			(*iter)->Process();
		}
	}

	void PlayerCrushCheck()
	{
		RECT temp;
		RECT playerRECT;
		RECT tileRECT;

		playerRECT.left = player->GetPosition().x;
		playerRECT.top = player->GetPosition().y;
		playerRECT.right = player->GetPosition().x + player->GetWidth();
		playerRECT.bottom = player->GetPosition().y + player->GetHeight() - 1;

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (TileInfos[i][j].tileinfo.GetIsMove() || !TileInfos[i][j].IsSet || TileInfos[i][j].tileinfo.GetImagePath() == (TCHAR*)TEXT(' ')) continue;

				tileRECT.left = TileInfos[i][j].position.x - 1;
				tileRECT.top = TileInfos[i][j].position.y - 1;
				tileRECT.right = TileInfos[i][j].position.x + TileInfos[i][j].tileinfo.GetWidth() - 1;
				tileRECT.bottom = TileInfos[i][j].position.y + TileInfos[i][j].tileinfo.GetHeight() - 1;


				if (IntersectRect(&temp, &playerRECT, &tileRECT))
				{
					player->MoveCancle();
				}
			}
		}
	}

	void BulletUpdate()
	{
		Bullet * pBullet;

		pBullet = player->GetBullet();

		if (pBullet != nullptr) pBullet->Update();

		//
		// 적 총알 업데이트
		//
		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			if ((*iter)->GetBullet() != nullptr)
			{
				(*iter)->GetBullet()->Update();
			}
		}
	}

	void BulletCrushCheck()
	{
		if (player->GetBullet() != nullptr)
		{
			if (!player->GetBullet()->GetIsDie()) BulletCrushCheck(player->GetBullet());
		}

		//
		// 적 총알 체크 추가.
		//

		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			if ((*iter)->GetBullet() != nullptr)
			{
				if (!(*iter)->GetBullet()->GetIsDie()) BulletCrushCheck((*iter)->GetBullet());
			}
		}
	}

	void BulletReleaseCheck()
	{
		if (player->GetBullet() != nullptr)
		{
			if (player->GetBullet()->GetIsDie())
			{
				if (BulletReleaseCheck(player->GetBullet()))
				{
					player->BulletRelease();
				}
			}
		}


		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			if ((*iter)->GetBullet() != nullptr)
			{
				if ((*iter)->GetBullet()->GetIsDie())
				{
					if (BulletReleaseCheck((*iter)->GetBullet()))
					{
						(*iter)->BulletRelease();
					}
				}
			}
		}
	}

	void BulletCrushCheck(Bullet* pBullet)
	{
		RECT temp;
		RECT BulletRECT;
		RECT tileRECT;

		BulletRECT.left = pBullet->GetPosition().x - 1;
		BulletRECT.top = pBullet->GetPosition().y - 1;
		BulletRECT.right = pBullet->GetPosition().x + pBullet->GetWidth() - 1;
		BulletRECT.bottom = pBullet->GetPosition().y + pBullet->GetHeight() - 1;

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (TileInfos[i][j].tileinfo.GetIsFloor() || TileInfos[i][j].tileinfo.GetIsTop() || !TileInfos[i][j].IsSet) continue;

				tileRECT.left = TileInfos[i][j].position.x - 1;
				tileRECT.top = TileInfos[i][j].position.y - 1;
				tileRECT.right = TileInfos[i][j].position.x + TileInfos[i][j].tileinfo.GetWidth() - 1;
				tileRECT.bottom = TileInfos[i][j].position.y + TileInfos[i][j].tileinfo.GetHeight() - 1;


				if (IntersectRect(&temp, &BulletRECT, &tileRECT))
				{
					if(TileInfos[i][j].tileinfo.GetIsDestory()) TileInfos[i][j].IsSet = false;	
					if (TileInfos[i][j].tileinfo.GetIsLife())
					{
						//
						// 라이프 테스트  코드
						// 
						SceneState = END;
					}
					pBullet->SetDie();
				}
			}
		}


		RECT playerRECT;

		if (pBullet->GetBullet() == ENEMYBULLET)
		{
			playerRECT.left = player->GetPosition().x;
			playerRECT.top = player->GetPosition().y;
			playerRECT.right = player->GetPosition().x + player->GetWidth();
			playerRECT.bottom = player->GetPosition().y + player->GetHeight() - 1;

			if (IntersectRect(&temp, &BulletRECT, &playerRECT))
			{
				//
				// 게임엔드 
				//
				pBullet->SetDie();
			}
		}
		else if (pBullet->GetBullet() == PLAYERBULLET)
		{
			vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();



			for (iter; iter != vEnemyPlayer.end();)
			{

				playerRECT.left = (*iter)->GetPosition().x;
				playerRECT.top = (*iter)->GetPosition().y;
				playerRECT.right = (*iter)->GetPosition().x + (*iter)->GetWidth();
				playerRECT.bottom = (*iter)->GetPosition().y + (*iter)->GetHeight() - 1;

				if (IntersectRect(&temp, &BulletRECT, &playerRECT))
				{
					//
					// 적 제거 코드
					//
					pBullet->SetDie();
					EnemyPlayer* temp = (*iter);

					iter = vEnemyPlayer.erase(iter);
					delete temp;
					temp = nullptr;
				}
				else
				{
					iter++;
				}
			}
		}
	}



	bool BulletReleaseCheck(Bullet* pBullet)
	{
		if (pBullet->GetIsDestory())
		{			
			return true;
		}
		else
		{
			return false;
		}
	}

	void DrawBullet()
	{
		DrawManager::Instance()->DrawBullet(player->GetBullet());
		//
		// 적 총알 추가.
		//

		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			DrawManager::Instance()->DrawBullet((*iter)->GetBullet());
		}
	} 

	void DrawPlayer()
	{

		DrawManager::Instance()->DrawPlayer((BasePlayer*)player);
		//
		// 적 드로우 추가
		//


		vector<EnemyPlayer*>::iterator iter = vEnemyPlayer.begin();

		for (iter; iter != vEnemyPlayer.end(); iter++)
		{
			DrawManager::Instance()->DrawPlayer((BasePlayer*)(*iter));
		}
	}

	void DrawBmp()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (TileInfos[i][j].IsSet)
				{
					if (TileInfos[i][j].IsSet)
					{
						if(!TileInfos[i][j].tileinfo.GetIsFloor()) DrawManager::Instance()->DrawBmp(TileInfos[i][j]);						
					}
				}
			}
		}
	}

	void DrawFloor()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (TileInfos[i][j].IsSet)
				{
					if (TileInfos[i][j].IsSet)
					{
						if (TileInfos[i][j].tileinfo.GetIsFloor()) DrawManager::Instance()->DrawFloor(TileInfos[i][j]);
					}
				}
			}
		}
	}
};

