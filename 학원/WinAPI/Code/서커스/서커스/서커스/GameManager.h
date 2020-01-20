#pragma once

#include "SingletonBase.h"
#include "CustomObject.h"
#include "Player.h"
#include "Background.h"
#include "DrawManager.h"
#include "ObjectPool.h"
#include "Enemy.h"

#define MOVELEFT 0
#define MOVERIGHHT 1
#define JUMP 2
#define IDLE 3


#define MENU 0
#define GAME 1

class GameManager : public SingletonBase<GameManager>
{
private:

	vector<CustomObject*> m_Objects;
	ObjectPool<Enemy> m_EnemyPool;
	Player* m_Player = nullptr;
	bool IsGameEnd = false;


	double CreateTime = 1000;
	double PreTime;


	double UpdateTime = 16;
	double PreUpdateTime = 0;

	int Dir = 0;
	int state = -1;

	int MinMove = 0;
	int MaxMove = 500;

	bool IsEndCreate = false;

	int GameState = MENU;

public:
	void Init()
	{
		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end();)
		{
			if ((*iter)->GetType() == ENEMY)
			{
				Enemy* obj = (Enemy*)*iter;
				bool result = obj->ReleaseCheck();

				if (obj->GetEnemyType() != ENEMY3 && obj->GetEnemyType() != ENEMY4)
				{
					m_EnemyPool.ReturnObject(obj);
					iter = m_Objects.erase(iter);
				}
				else
				{
					iter++;
				}

			}
			else
			{
				iter++;
			}
		}
		
		for (iter = m_Objects.begin(); iter != m_Objects.end();iter++)
		{
			delete *iter;
		}
		m_Objects.clear();
		if (m_Player != nullptr)
		{
			m_Player = nullptr;
		}
		m_EnemyPool.PoolClear();
		IsGameEnd = false;
		IsEndCreate = false;
		MinMove = 0;
		MaxMove = 500;
		UpdateTime = 16;
		PreUpdateTime = 0;
		Dir = 0;
		state = -1;

		PreTime = clock();
		m_Player = new Player(200, 600);
		m_Objects.push_back(m_Player);
		m_Objects.push_back(new Background(WEED, 0, 268));

		for (int i = -15; i < -2; i++)
		{
			m_Objects.push_back(new Background(HUMAN, 64 * i, 210));
		}

		m_Objects.push_back(new Background(DECO, 64 * -2, 206));

		m_Objects.push_back(new Background(HUMAN, 64 * -1, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 0, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 1, 210));

		for (int i = 2; i < 14; i++)
		{
			m_Objects.push_back(new Background(HUMAN, 64 * i, 210));
		}

		m_Objects.push_back(new Background(DECO, 64 * 14, 206));

		m_Objects.push_back(new Background(HUMAN, 64 * 15, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 16, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 17, 210));

		m_Objects.push_back(new Background(MITER, 1000, 680,(TCHAR*)TEXT("200")));

		m_EnemyPool.SetPool(10);
	}

	bool GetGameEnd()
	{
		return IsGameEnd;
	}

	void RetryGame()
	{
		PreTime = clock();
		IsGameEnd = false;
		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end();)
		{
			if ((*iter)->GetType() == ENEMY)
			{
				Enemy* obj = (Enemy*)(*iter);
				obj->Release();
				
				if (EnemyReleseCheck(obj))
				{
					iter = m_Objects.erase(iter);
				}
				else
				{
					iter++;
				}			
			}
			else
			{
				iter++;
			}

		}
	}

	void Draw(HDC hdc)
	{
		DrawManager::Instance()->Draw(hdc, m_Objects.begin(), m_Objects.end());
	}

	void Update(HDC hdc,HWND hWnd)
	{
		if (GameState == MENU)
		{
			HDC g_MemDC = CreateCompatibleDC(hdc);
			HBITMAP bitmap = CreateCompatibleBitmap(g_MemDC, 1024, 768);
			HBITMAP old = (HBITMAP)SelectObject(g_MemDC, bitmap);
			
			//DeleteObject(bitmap);

			TextOut(g_MemDC, 500, 300, TEXT("찰리 서커스"), sizeof("찰리 서커스") - 1);
			TextOut(g_MemDC, 400, 350, TEXT("좌우 이동 : 키보드화살표 / 점프 : 스페이스"), sizeof("좌우 이동 : 키보드화살표 / 점프 : 스페이스") - 1);
			TextOut(g_MemDC, 500, 400, TEXT("시작 : 엔터"), sizeof("시작 : 엔터") - 1);
			TextOut(g_MemDC, 450, 450, TEXT("게임종료후 : 백스페이스"), sizeof("게임종료후 : 백스페이스") - 1);

			BitBlt(hdc, 0, 0, 1024, 768, g_MemDC, 0, 0, SRCCOPY);
			DeleteDC(g_MemDC);
			KeyStateUpdate();
		}
		else if(GameState == GAME)
		{
			if (clock() - PreUpdateTime > UpdateTime)
			{
				KeyStateUpdate();
				if (!IsGameEnd)
				{
					Process();
					PlayerStateUpdate();
					JumpMoveUpdate();
					CreateEnemy();
					int crashcheck = PlayerCrashCheck();
					if (crashcheck != -1)
					{
						IsGameEnd = true;
						if (crashcheck == ENEMY3)
						{
							m_Player->SetWin();
							SetHumanAnimation(true);
						}
						else
						{
							m_Player->SetLose();
						}
					}
				}
				Draw(hdc);
				PreUpdateTime = clock();
			}
		}
	
	}


	void SetHumanAnimation(bool value)
	{
		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end();iter++)
		{
			if ((*iter)->GetType() == BACKGROUND)
			{
				Background* obj = (Background*)(*iter);

				if (obj->GetBackGroundType() == HUMAN)
				{
					obj->SetAnimationPlay(value);
				}
			}
		}
	}

	void Move(int Dir)
	{
		//if (Dir == -1)return;
		if (MinMove >= 0 && Dir == LEFT) return;

		MinMove += Dir;

		if (IsEndCreate)
		{
			MaxMove += Dir;
			if (MaxMove <= 0)
			{
				m_Player->Move(-Dir);
				return;
			}
		}

		if (IsGameEnd) return;

		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end();iter++)
		{
			(*iter)->Scroll(Dir);
			(*iter)->SetScrollDir(Dir);
		}
	}

	int PlayerCrashCheck()
	{
		vector<CustomObject*>::iterator iter;
		int result = -1;
		for (iter = m_Objects.begin(); iter != m_Objects.end(); )
		{
			if ((*iter)->GetType() == ENEMY)
			{
				Enemy* obj = (Enemy*)(*iter);
				if (m_Player->CrashCheck(obj->GetCrashRECT()))
				{
					result = obj->GetEnemyType();
					if (result == ENEMY3)
					{
						m_Player->SetY(obj->GetYpos());
					}
					else
					{
						obj->Release();
					}
					return result;
				}
				else
				{
					iter++;
				}
			}
			else
			{
				iter++;
			}

		}

		return -1;
	}

	void Process()
	{

		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end(); )
		{
			(*iter)->Process();

			if ((*iter)->GetType() == BACKGROUND)
			{
				Background* obj = (Background*)(*iter);
				if (obj->GetBackGroundType() == MITER)
				{
					if (obj->GetiMiter() <= 0)
					{
						//
						// ENDING 생성.
						//
						if (!IsEndCreate)
						{
							IsEndCreate = true;

							Enemy* add = new Enemy();
							add->SetData(ENEMY3);

							Enemy* add2 = new Enemy();
							add2->SetData(ENEMY4);

							m_Objects.push_back(add);
							m_Objects.push_back(add2);
							
						}
					}
				}
			}

			if ((*iter)->GetType() == ENEMY)
			{
				if (EnemyReleseCheck((Enemy*)(*iter)))
				{
					iter = m_Objects.erase(iter);
				}
				else
				{
					iter++;
				}		
			}
			else
			{
				iter++;
			}
			
		}
	}

	bool EnemyReleseCheck(Enemy* obj)
	{
		bool result = obj->ReleaseCheck();
		if (obj->ReleaseCheck())
		{
			m_EnemyPool.ReturnObject(obj);
		}
		return result;
	}



	
	void Jump()
	{
		for (int i = 0; i < m_Objects.size(); i++)
		{
			if (m_Objects[i]->GetType() == PLAYER)
			{
				Player* obj = (Player*)m_Objects[i];
				obj->SetJump();
			}
		}
	}

	void CreateEnemy()
	{
		if (IsGameEnd) return;

		if (clock() - PreTime > CreateTime)
		{
			srand((unsigned int)time(NULL));

			int randomValue = rand() % 2;
			CreateTime = rand() % 3000 + 1500;

			Enemy* add = (Enemy*)m_EnemyPool.Pooling();
			if (add == nullptr) return;
			add->SetData(randomValue);
			m_Objects.push_back(add);

			PreTime = clock();
		}	
	}



		//설명

		//0x0000

		//이전에 누른 적이 없고 호출 시점에도 눌려있지 않은 상태

		//0x0001

		//이전에 누른 적이 있고 호출 시점에는 눌려있지 않은 상태

		//0x8000

		//이전에 누른 적이 없고 호출 시점에는 눌려있는 상태

		//0x8001

		//이전에 누른 적이 있고 호출 시점에도 눌려있는 상태


	//
	// 점프 할 때 방향을 준다 방향이 없으면 위로만 점프를 한다.
	//
	void KeyStateUpdate()
	{
		if (GameState == GAME)
		{
			if (GetKeyState(VK_SPACE) & 0x8000)
			{
				state = JUMP;
				return;
			}

			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				state = MOVERIGHHT;
				return;
			}

			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				state = MOVELEFT;
				return;
			}

			state = IDLE;

			if (IsGameEnd)
			{
				if (GetKeyState(VK_BACK) & 0x8000)
				{
					GameState = MENU;
					return;
				}
			}
		}
		else
		{
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				GameState = GAME;
				Init();
				return;
			}
		}

	}

	void PlayerStateUpdate()
	{
		switch (state)
		{
		case MOVERIGHHT:
			{
				if (m_Player->IsMove())
				{
					Dir = RIGHT;
					m_Player->SetMove();
					Move(RIGHT);
				}
				break;
			}
		case MOVELEFT:
			{
				if (m_Player->IsMove())
				{
					Dir = LEFT;
					m_Player->SetMove();
					Move(LEFT);
				}
				break;
			}
		case JUMP:
			{
				Jump();
				break;
			}
		case IDLE:
			{
				if (m_Player->IsMove())
				{
					m_Player->SetIdle();
					Dir = -1;
					Move(0);
				}
				break;
			}
		default:
			break;
		}
	}

	void JumpMoveUpdate()
	{
		if (!m_Player->IsMove())
		{
			if (Dir != -1)
			{
				Move(Dir);
			}
		}
	}
	
};

