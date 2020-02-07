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
	
	//각 타일에서 도착지까지의 비용 계산 필요
	class PathFindTileInfo
	{
	public:
		MapToolTile maptooltile;
		int r;	// 움직인 거리 / 댑스가 증가 할 수록 1씩 증가.
		int h;	// 도착 지점 까지의 최소 값 / 타일 하나당 이동거리는 1이라고 가정한다.
	};

	class CustomPoint
	{
	public:
		POINT point;	// 좌표
		int count;		// 시작 지점에서 이동한 위치
		int row;		// 현재 포인트 정보가 위치한 타일인포의 row
		int col;		// 현재 포인트 정보가 위치한 타일인포의 col
		bool IsFind = false;	// 재 탐색에 포함 될것인지 확인 하는 변수.
		int dir;
		CustomPoint* pre = nullptr;
		//CustomPoint* next = nullptr;
	};

	int precount = -1; // 길을 검색 도중에 막힌 길이 나와 그전으로 돌아가야 할 경우에 이동경로에 저장된 패스를 삭제 하기 위해 존재.

	vector<CustomPoint*> vPath;	// 해당 좌표 순서대로 움직여야 한다.
	vector<CustomPoint*> openpath;	// 탐색 가능한 길
	//vector<CustomPoint*> closepath;	// 탐색이 완료되어 탐색 할 필요가 없는 길
	
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
			// 시작 할때는 시작 위치 주변 4방향을 조건에 맞춰 오픈 해 준다
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
			// 기댓값이 가장 작은 값을 찾는다.
			// 오픈 패스 찾을 때 해당 위치가 이미 클로즈 패스에 있으면 제외한다.
			// 해당 위치에서 이동가능한 패스들이 이미 오픈되었거나 탐색이 완료 되었다면 해당 포인트는 탐색완료 처리하고 다음으로 기댓값이 낮은 곳으로 이동하여 재탐색한다.
			// 기대값 위치로 진행을 하였을 경우에 막힌 길이라면 기대값을 올려준다.
			// 기대값 을 뭘로 추가 해 줄것이냐.

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
			// 길 찾기 완료 검사
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
			// 추가 탐색 가능 경로 오픈
			//
			OpenPath(min, tile);

			
		
		}

		return true;
	}


	void OpenPath(CustomPoint* startPoint, MapToolTile tile[19][19])
	{
		//
		// closepath에 대한 예외처리 추가.
		// openpath에 대한 예외 처리 추가.
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
	// 가장 작은 기대값 찾기
	// 객체가 현재 위치한 곳에서 가장 가까운 곳을 찾는다
	// 길을 찾을수가 없으면 전위치로 돌아가고 해당 위치는 더이상 탐색 하지 않게 처리한다.
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
		// 시작 지점에서 4 방향 r + h 값이 방향 위주로 풀어 간다. 방향은 좌 우 상 하 순으로 움직인다. 
		// 시작 지점에서 4방향 검사를 실시 하고 4방향이 맵타일을 벗어 나지 않으면 openpath에 저장 되고 각 방향별로 반복 된다.
		// 첫번째가 아니면 현재 커스텀 포인트의 카운트를 1증가해서 받는다

		bool IsFirst = true;
		

		while (PathFind(tile,IsFirst))
		{
			IsFirst = false;
		}
	}
};

