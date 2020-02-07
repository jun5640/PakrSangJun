#pragma once

#include "BaseAI.h"
#include "CommonFeature.h"
#include <vector>

using namespace std;

#define CLOSECOUNT 10000

#define MOVEUP 0
#define MOVEDOWN 1
#define MOVERIGHT 2
#define MOVELEFT 3

class Astar : public BaseAI
{
	
	//�� Ÿ�Ͽ��� ������������ ��� ��� �ʿ�
	class PathFindTileInfo
	{
	public:
		MapToolTile maptooltile;
		int r;	// ������ �Ÿ� / �𽺰� ���� �� ���� 1�� ����.
		int h;	// ���� ���� ������ �ּ� �� / Ÿ�� �ϳ��� �̵��Ÿ��� 1�̶�� �����Ѵ�.
	};

	class CustomPoint
	{
	public:
		POINT point;	// ��ǥ
		int count;		// ���� �������� �̵��� ��ġ
		int row;		// ���� ����Ʈ ������ ��ġ�� Ÿ�������� row
		int col;		// ���� ����Ʈ ������ ��ġ�� Ÿ�������� col
		bool IsFind = false;	// �� Ž���� ���� �ɰ����� Ȯ�� �ϴ� ����.
		int dir;
		CustomPoint* pre = nullptr;
		//CustomPoint* next = nullptr;
	};

	int precount = -1; // ���� �˻� ���߿� ���� ���� ���� �������� ���ư��� �� ��쿡 �̵���ο� ����� �н��� ���� �ϱ� ���� ����.

	vector<CustomPoint*> vPath;	// �ش� ��ǥ ������� �������� �Ѵ�.
	vector<CustomPoint*> openpath;	// Ž�� ������ ��
	//vector<CustomPoint*> closepath;	// Ž���� �Ϸ�Ǿ� Ž�� �� �ʿ䰡 ���� ��
	
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	
	CustomPoint* preCustomPoint = nullptr;

	CustomPoint* header = nullptr;
	CustomPoint* cur = nullptr;

public:

	bool PathFind(MapToolTile tile[19][19],bool isfirst)
	{
		if (isfirst)
		{
			//
			// ���� �Ҷ��� ���� ��ġ �ֺ� 4������ ���ǿ� ���� ���� �� �ش�
			// 
			CustomPoint* startPoint = new CustomPoint();
			startPoint->point.x = tile[startRow][startCol].position.x;
			startPoint->point.y = tile[startRow][startCol].position.y;
			startPoint->count = 1;
			startPoint->row = startRow;
			startPoint->col = startCol;

			openpath.push_back(startPoint);
			OpenPath(startPoint, tile);
		}
		else
		{
			//
			// ����� ���� ���� ���� ã�´�.
			// ���� �н� ã�� �� �ش� ��ġ�� �̹� Ŭ���� �н��� ������ �����Ѵ�.
			// �ش� ��ġ���� �̵������� �н����� �̹� ���µǾ��ų� Ž���� �Ϸ� �Ǿ��ٸ� �ش� ����Ʈ�� Ž���Ϸ� ó���ϰ� �������� ����� ���� ������ �̵��Ͽ� ��Ž���Ѵ�.
			// ��밪 ��ġ�� ������ �Ͽ��� ��쿡 ���� ���̶�� ��밪�� �÷��ش�.
			// ��밪 �� ���� �߰� �� �ٰ��̳�.

			CustomPoint *min = FindMinExpectValue();


			if (precount >= min->count)
			{
				erasepath(min->count);
				//eraseprepath(preCustomPoint);
				preCustomPoint->IsFind = true;
				precount = min->count;
				//preCustomPoint->count = 10000;
			}
			else
			{
				precount = min->count;
			}

			preCustomPoint = min;

			vPath.push_back(min);

			//
			// �� ã�� �Ϸ� �˻�
			//

			int minrowdif = endRow - min->row;
			int mincoldif = endCol - min->col;

			if (minrowdif < 0) minrowdif = minrowdif * -1;
			if (mincoldif < 0) mincoldif = mincoldif * -1;

			if (minrowdif + mincoldif == 1)
			{
				//erasepath();
				return false;
			}

			//
			// �߰� Ž�� ���� ��� ����
			//
			OpenPath(min, tile);

			
		
		}

		return true;
	}


	void OpenPath(CustomPoint* startPoint, MapToolTile tile[19][19])
	{
		//
		// closepath�� ���� ����ó�� �߰�.
		// openpath�� ���� ���� ó�� �߰�.
		//


		if (startPoint->row - 1 >= 0)
		{
			if (!IsContain(tile[startPoint->row - 1][startPoint->col]) && IsMove(tile[startPoint->row - 1][startPoint->col]))
			{
				CustomPoint *add = new CustomPoint();;
				add->point.x = tile[startPoint->row - 1][startPoint->col].position.x;
				add->point.y = tile[startPoint->row - 1][startPoint->col].position.y;
				add->count = startPoint->count + 1;
				add->row = startPoint->row - 1;
				add->col = startPoint->col;
				add->pre = startPoint;
				add->dir = MOVELEFT;
				openpath.push_back(add);
			}
		}

		if (startPoint->row + 1 < 19)
		{
			if (!IsContain(tile[startPoint->row + 1][startPoint->col]) && IsMove(tile[startPoint->row + 1][startPoint->col]))
			{
				CustomPoint *add = new CustomPoint();;
				add->point.x = tile[startPoint->row + 1][startPoint->col].position.x;
				add->point.y = tile[startPoint->row + 1][startPoint->col].position.y;
				add->count = startPoint->count + 1;
				add->row = startPoint->row + 1;
				add->col = startPoint->col;
				add->pre = startPoint;
				add->dir = MOVERIGHT;
				openpath.push_back(add);
			}
		}

		if (startPoint->col - 1 >= 0)
		{
			if (!IsContain(tile[startPoint->row][startPoint->col - 1]) && IsMove(tile[startPoint->row][startPoint->col - 1]))
			{
				CustomPoint *add = new CustomPoint();;
				add->point.x = tile[startPoint->row][startPoint->col - 1].position.x;
				add->point.y = tile[startPoint->row][startPoint->col - 1].position.y;
				add->count = startPoint->count + 1;
				add->row = startPoint->row;
				add->col = startPoint->col - 1;
				add->pre = startPoint;
				add->dir = MOVEUP;
				openpath.push_back(add);
			}
		}

		if (startPoint->col + 1 < 19)
		{
			if (!IsContain(tile[startPoint->row][startPoint->col + 1]) && IsMove(tile[startPoint->row][startPoint->col + 1]))
			{
				CustomPoint *add = new CustomPoint();;
				add->point.x = tile[startPoint->row][startPoint->col + 1].position.x;
				add->point.y = tile[startPoint->row][startPoint->col + 1].position.y;
				add->count = startPoint->count + 1;
				add->row = startPoint->row;
				add->col = startPoint->col + 1;
				add->pre = startPoint;
				add->dir = MOVEDOWN;
				openpath.push_back(add);
			}
		}

		//startPoint->count = CLOSECOUNT;
		//eraseOpenpath(startPoint->point);
		//closepath.push_back(startPoint);
	}

	bool IsContain(MapToolTile tile)
	{
		if (ContainOpenpath(tile.position))
		{
			return true;
		}
		 
		return false;
	}

	bool IsMove(MapToolTile tile)
	{
		if ((tile.IsSet && tile.tileinfo.GetIsMove()) || !tile.IsSet)
		{
			return true;
		}
		
		return false;
	}

	bool ContainOpenpath(POINT point)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = openpath.begin(); iter != openpath.end(); iter++)
		{
			if ((*iter)->point.x == point.x && (*iter)->point.y == point.y)
			{
				return true;
			}
		}

		return false;
	}

 

	/*bool ContainClosepath(POINT point)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = closepath.begin(); iter != closepath.end(); iter++)
		{
			if ((*iter)->point.x == point.x && (*iter)->point.y == point.y)
			{
				return true;
			}
		}

		return false;
	}*/

	void eraseOpenpath(POINT point)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = openpath.begin(); iter != openpath.end();)
		{
			if ((*iter)->point.x == point.x && (*iter)->point.y == point.y)
			{
				iter = openpath.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void erasepath(int count)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = vPath.begin(); iter != vPath.end();)
		{
			if ((*iter)->count >= count)
			{
				iter = vPath.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void erasepath()
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = vPath.begin(); iter != vPath.end();)
		{
			if ((*iter)->count >= 10000)
			{
				iter = vPath.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void eraseprepath(CustomPoint* point)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = vPath.begin(); iter != vPath.end();)
		{
			if ((*iter)->point.x == point->point.x && (*iter)->point.y == point->point.y)
			{
				iter = vPath.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	POINT GetPoint()
	{
		if (vPath.size() == 0)
		{
			POINT point;
			point.x = -1;
			point.y = -1;

			return point;
		}
		
		return (*vPath.begin())->point;
	}

	int GetDir()
	{
		if (vPath.size() == 0)
		{
			return -100;
		}
		return (*vPath.begin())->dir;
	}

	void erasepath(POINT point)
	{
		vector<CustomPoint*>::iterator iter;

		for (iter = vPath.begin(); iter != vPath.end();)
		{
			if ((*iter)->point.x == point.x && (*iter)->point.y == point.y)
			{
				iter = vPath.erase(iter);
			}
		else
			{
				iter++;
			}
		}
	}

	//
	// ���� ���� ��밪 ã��
	// ��ü�� ���� ��ġ�� ������ ���� ����� ���� ã�´�
	// ���� ã������ ������ ����ġ�� ���ư��� �ش� ��ġ�� ���̻� Ž�� ���� �ʰ� ó���Ѵ�.
	//
	CustomPoint* FindMinExpectValue()
	{
		vector<CustomPoint*>::iterator iter;

		CustomPoint *min = nullptr;

		if (openpath.size() == 1) return *openpath.begin();

		for (iter = openpath.begin(); iter != openpath.end(); iter++)
		{
			if ((*iter)->IsFind) continue;

			int minExpectValue = 10000;

			if (min != nullptr)
			{
				int minrowdif = endRow - min->row;
				int mincoldif = endCol - min->col;

				if (minrowdif < 0) minrowdif = minrowdif * -1;
				if (mincoldif < 0) mincoldif = mincoldif * -1;

				minExpectValue = minrowdif + mincoldif + min->count;
			}

			int rowdif = endRow - (*iter)->row;
			int coldif = endCol - (*iter)->col;

			if (rowdif < 0) rowdif = rowdif * -1;
			if (coldif < 0) coldif = coldif * -1;

			int expectValue = rowdif + coldif + (*iter)->count;

			if (expectValue <= minExpectValue && precount < (*iter)->count)
			{ 
				min = (*iter);
			}
		}

		if (min == nullptr)
		{
			min = preCustomPoint->pre;
			return min;
		}
		else
		{
			return min;
		}
	}

	void SetPath(int startRowValue, int startColValue, int endRowValue, int endColValue, MapToolTile tile[19][19])
	{		
		startRow = startRowValue;
		startCol = startColValue;
		endRow = endRowValue;
		endCol = endColValue;

		//
		// ���� �������� 4 ���� r + h ���� ���� ���ַ� Ǯ�� ����. ������ �� �� �� �� ������ �����δ�. 
		// ���� �������� 4���� �˻縦 �ǽ� �ϰ� 4������ ��Ÿ���� ���� ���� ������ openpath�� ���� �ǰ� �� ���⺰�� �ݺ� �ȴ�.
		// ù��°�� �ƴϸ� ���� Ŀ���� ����Ʈ�� ī��Ʈ�� 1�����ؼ� �޴´�

		bool IsFirst = true;
		

		while (PathFind(tile,IsFirst))
		{
			IsFirst = false;
		}
	}
};

