#pragma once

#include "SingletonBase.h"
#include "CustomObject.h"
#include "Player.h"
#include "Background.h"
#include "DrawManager.h"
#include "ObjectPool.h"
#include "Enemy.h"

class GameManager : public SingletonBase<GameManager>
{
private:

	vector<CustomObject*> m_Objects;
	ObjectPool<Enemy> m_EnemyPool;
	Player* m_Player;
	bool IsGameEnd = false;
	bool FirstInit = false;


	double CreateTime = 1000;
	double PreTime;

	double GameEndTime = 30000; // 30√ 
	double GameEndPreTime = 0;

public:
	void Init()
	{
		PreTime = clock();
		GameEndPreTime = clock();
		m_Player = new Player(200, 600);
		m_Objects.push_back(m_Player);
		m_Objects.push_back(new Background(WEED, 0, 268));

		for (int i = 0; i < 12; i++)
		{
			m_Objects.push_back(new Background(HUMAN, 64 * i, 210));
		}

		m_Objects.push_back(new Background(DECO, 64 * 12, 206));
		m_Objects.push_back(new Background(HUMAN, 64 * 13, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 14, 210));
		m_Objects.push_back(new Background(HUMAN, 64 * 15, 210));

		if (!FirstInit)
		{
			FirstInit = true;
			m_EnemyPool.SetPool(10);
		}
		
	}

	bool GetGameEnd()
	{
		return IsGameEnd;
	}

	void RetryGame()
	{
		PreTime = clock();
		GameEndPreTime = clock();
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



		Process();
		if (PlayerCrashCheck())
		{
			IsGameEnd = true;
			if (MessageBox(hWnd, TEXT("Game Over"), TEXT("Game Over"), MB_OK) == IDOK)
			{
				RetryGame();
			}
		}
		Draw(hdc);
		CreateEnemy();
		GameEndTimeCheck(hWnd);
	
	}

	bool PlayerCrashCheck()
	{
		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end(); )
		{
			if ((*iter)->GetType() == ENEMY)
			{
				Enemy* obj = (Enemy*)(*iter);
				if (m_Player->CrashCheck(obj->GetCrashRECT()))
				{
					obj->Release();

					iter = m_Objects.erase(iter);
					return true;
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

		return false;
	}

	void Process()
	{

		vector<CustomObject*>::iterator iter;

		for (iter = m_Objects.begin(); iter != m_Objects.end(); )
		{
			(*iter)->Process();

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

	void GameEndTimeCheck(HWND hWnd)
	{
		if (IsGameEnd) return;

		if (clock() - GameEndPreTime > GameEndTime)
		{
			IsGameEnd = true;

			if (MessageBox(hWnd, TEXT("Game Clear"), TEXT("Game Clear"), MB_OK) == IDOK)
			{
				RetryGame();
			}
		}
	}
	
};

