#pragma once
#pragma comment(lib,"Msimg32.lib");

#include "SingletonBase.h"
#include "TileInfo.h"


class BitMapManager : public SingletonBase<BitMapManager>
{
protected:

	//vector<BitMapInfo> m_vBitMapInfo;
	vector<TileInfo> m_vTileInfo;

	HBITMAP myBitmap, oldBitmap, hImage, hOldBitmap;

	int preSource = -1;
	TCHAR* tilecolorPath;

	TileInfo * FirstClick = nullptr;
public:
	int DelayTime = 0;

	BitMapManager() {};
	~BitMapManager() {};
	void TileSelectCheck(int x, int y, int TeamType);
	
	void InitSelect()
	{
		FirstClick = nullptr;
	}

	void DrawAllTile(HDC hdc, HDC MemDC, HINSTANCE hInst)
	{

		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		for (iter; iter != m_vTileInfo.end(); iter++)
		{
			

			if (iter->TileColorType == BROWNTILE)
			{
				tilecolorPath = (TCHAR*)TEXT("Res/block01.bmp");
				
			}
			else
			{
				tilecolorPath = (TCHAR*)TEXT("Res/block0.bmp");
			}

			hImage = (HBITMAP)LoadImage(NULL, tilecolorPath,
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			hOldBitmap = (HBITMAP)SelectObject(MemDC, hImage);
			
			TransparentBlt(hdc, iter->m_rt.left,iter->m_rt.top, iter->width,iter->width, MemDC, 0, 0, iter->width, iter->width, RGB(255, 0, 255));

			SelectObject(MemDC, hOldBitmap);
			DeleteObject(hImage);
			
			if (iter->m_piece != nullptr)
			{
				hImage = (HBITMAP)LoadImage(NULL, iter->m_piece->GetImagePath(),
					IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

				hOldBitmap = (HBITMAP)SelectObject(MemDC, hImage);

				TransparentBlt(hdc, iter->m_rt.left, iter->m_rt.top, iter->width, iter->width, MemDC, 0, 0, iter->width, iter->width, RGB(255, 0, 255));

				SelectObject(MemDC, hOldBitmap);
				DeleteObject(hImage);
			}
		}

		DeleteDC(MemDC);
	}

	void RegisterTileInfo(TileInfo info)
	{
		m_vTileInfo.push_back(info);
	}

	static BitMapManager* Instance()
	{
		if (_Instance == nullptr)
		{
			_Instance = new BitMapManager;
		}
		return _Instance;
	}

	



	bool WallCheck(int PieceType,int deltaX,int deltaY)
	{
		if (PieceType == BISHOP)
		{
			return BISHOPWallCheck(deltaX, deltaY);
		}
		else if (PieceType == QUEEN)
		{
			if (deltaX == 0 || deltaY == 0)
			{
				return ROOKWallCheck(deltaX, deltaY);
			}
			else
			{
				return BISHOPWallCheck(deltaX, deltaY);
			}
		}
		else if (PieceType == ROOK)
		{
			return ROOKWallCheck(deltaX, deltaY);
		}

		return false;
	}

	bool BISHOPWallCheck(int input_deltaX, int input_deltaY)
	{
		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		while (true)
		{
			if (input_deltaX < 0) input_deltaX++;
			else input_deltaX--;
			if (input_deltaY < 0) input_deltaY++;
			else input_deltaY--;

			if (input_deltaX == 0) break;

			for (iter = m_vTileInfo.begin(); iter != m_vTileInfo.end(); iter++)
			{
				int deltaX = (FirstClick->m_rt.left - iter->m_rt.left) / FirstClick->width;
				int deltaY = (FirstClick->m_rt.top - iter->m_rt.top) / FirstClick->height;

				if (deltaX == input_deltaX && deltaY == input_deltaY)
				{
					if (iter->m_piece != nullptr)return true;
				}
			}

			
		}

		return false;
	}

	bool ROOKWallCheck(int input_deltaX, int input_deltaY)
	{
		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		while (true)
		{
			if (input_deltaX == 0 && input_deltaY < 0) input_deltaY++;
			else if (input_deltaX == 0 && input_deltaY > 0)input_deltaY--;
		
			if (input_deltaY == 0 && input_deltaX < 0) input_deltaX++;
			else if (input_deltaY == 0 && input_deltaX > 0)input_deltaX--;

			if (input_deltaX == 0 && input_deltaY == 0) break;

			for (iter = m_vTileInfo.begin(); iter != m_vTileInfo.end(); iter++)
			{
				int deltaX = (FirstClick->m_rt.left - iter->m_rt.left) / FirstClick->width;
				int deltaY = (FirstClick->m_rt.top - iter->m_rt.top) / FirstClick->height;

				if (deltaX == input_deltaX && deltaY == input_deltaY)
				{
					if (iter->m_piece != nullptr)return true;
				}
			}


		}

		return false;
	}

	void DeleteData()
	{
		vector<TileInfo>::iterator iter = m_vTileInfo.begin();

		for (iter; iter != m_vTileInfo.end(); iter++)
		{
			delete iter->m_piece;
			iter->m_piece = nullptr;

		}

		m_vTileInfo.clear();	
	}
};

