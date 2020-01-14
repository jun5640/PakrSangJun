#include "BitMapManager.h"
#include "GameManager.h"

BitMapManager* BitMapManager::_Instance = nullptr;



void BitMapManager::TileSelectCheck(int x, int y, int TeamType)
{
	POINT pt;
	pt.x = x;
	pt.y = y;

	vector<TileInfo>::iterator iter = m_vTileInfo.begin();

	for (iter; iter != m_vTileInfo.end(); iter++)
	{
		if (PtInRect(&(iter->m_rt), pt))
		{
			if (iter->m_piece != nullptr)
			{
				if (FirstClick == nullptr)
				{
					if (TeamType == iter->m_piece->GetTeamType())FirstClick = &(*iter);
					break;
				}
				else
				{
					//
					// 같은 팀이 아닐때 혹은 빈곳 일때의 조건문 해당 이동쪽에 상대 말이 있을경우 할댕해제도 해줘야 한다.
					//

					int deltaX = (FirstClick->m_rt.left - iter->m_rt.left) / FirstClick->width;
					int deltaY = (FirstClick->m_rt.top - iter->m_rt.top) / FirstClick->height;

					if (WallCheck(FirstClick->m_piece->GetPieceType(), deltaX, deltaY)) break;

					if (FirstClick->m_piece->Process(iter->m_piece, deltaX, deltaY) && !WallCheck(FirstClick->m_piece->GetPieceType(), deltaX, deltaY))
					{
						if (iter->m_piece != FirstClick->m_piece)
						{
							if (iter->m_piece != nullptr && iter->m_piece->GetPieceType() == KING)
							{
								//
								// 게임종료
								//
								FirstClick = nullptr;
								DeleteData();
								GameManager::Instance()->Init();
								return;
							}

							if (FirstClick->m_piece != nullptr && FirstClick->m_piece->GetPieceType() == PAWN)
							{
								if (FirstClick->m_piece->GetUpgrade() == 6)
								{
									delete FirstClick->m_piece;
									FirstClick->m_piece = new Queen(TeamType);
								}
							}

							if (iter->m_piece != nullptr)
							{
								delete iter->m_piece;
								iter->m_piece = nullptr;
							}
							iter->m_piece = FirstClick->m_piece;
							FirstClick->m_piece = nullptr;
							FirstClick = nullptr;
							GameManager::Instance()->ChangeTurn();
						}
					}
				}
			}
			else
			{
				if (FirstClick != nullptr)
				{
					//
					// 같은 팀이 아닐때 혹은 빈곳 일때의 조건문 해당 이동쪽에 상대 말이 있을경우 할댕해제도 해줘야 한다.
					//



					int deltaX = (FirstClick->m_rt.left - iter->m_rt.left) / FirstClick->width;
					int deltaY = (FirstClick->m_rt.top - iter->m_rt.top) / FirstClick->height;

					if (FirstClick->m_piece->Process(iter->m_piece, deltaX, deltaY) && !WallCheck(FirstClick->m_piece->GetPieceType(), deltaX, deltaY))
					{
						if (iter->m_piece != FirstClick->m_piece)
						{
							
							if (iter->m_piece != nullptr && iter->m_piece->GetPieceType() == KING)
							{
								//
								// 게임종료
								//
								FirstClick = nullptr;
								DeleteData();
								GameManager::Instance()->Init();
								return;
							}

							if (FirstClick->m_piece != nullptr && FirstClick->m_piece->GetPieceType() == PAWN)
							{
								if (FirstClick->m_piece->GetUpgrade() == 6)
								{
									delete FirstClick->m_piece;
									FirstClick->m_piece = new Queen(TeamType);
								}
							}

							if (iter->m_piece != nullptr)
							{
								delete iter->m_piece;
								iter->m_piece = nullptr;
							}
							iter->m_piece = FirstClick->m_piece;
							FirstClick->m_piece = nullptr;
							FirstClick = nullptr;
							GameManager::Instance()->ChangeTurn();
						}
					}
				}
			}
		}
	}
}