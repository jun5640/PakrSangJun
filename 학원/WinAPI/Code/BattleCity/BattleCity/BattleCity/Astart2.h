#pragma once

#include "BaseAI.h"
#include "CommonFeature.h"
#include <vector>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

class Astar2 : public BaseAI
{
private:

	class AstarNode
	{
	public:
		int value = 0;	//��밪
		POINT point;
		int row;
		int col;
		bool ischecked = false; //�켱 Ž���� ���� ����.
		int count;
		AstarNode* Node_left = nullptr;
		AstarNode* Node_right = nullptr;
		AstarNode* Node_down = nullptr;
		AstarNode* Node_up = nullptr;
		
		int addvalue = 0;	// �ѹ� �˻��ߴ� ģ������ �߰��Ѵ�.
	};
	
	class CustomPoint
	{
	public:
		POINT point;	// ��ǥ
		int count;		// ���� �������� �̵��� ��ġ
		int row;		// ���� ����Ʈ ������ ��ġ�� Ÿ�������� row
		int col;		// ���� ����Ʈ ������ ��ġ�� Ÿ�������� col
	};

	int startRow;
	int startCol;
	int endRow;
	int endCol;

	int minvalue = 0;

	bool PathFindEnd = false;
	bool IsFirst = true;

	AstarNode * header = nullptr;

public:

	vector<CustomPoint*> vPath;

	int ExpectValue(int row, int col,int count)
	{
		int value3 = endRow - row;
		int value4 = endCol - col;


		if (value3 < 0) value3 = value3 * -1;
		if (value4 < 0) value4 = value4 * -1;

		return value3 + value4 + count;
	}

	bool IsMove(MapToolTile tile)
	{
		if ((tile.IsSet && tile.tileinfo.GetIsMove()) || !tile.IsSet)
		{
			return true;
		}

		return false;
	}



	void PathFind(MapToolTile tile[19][19], int row, int col, AstarNode* node, int dir)
	{
		node->ischecked = true;
		node->addvalue++;

		bool check = false;
		if (row - 1 >= 0 && dir != RIGHT && node->Node_left == nullptr)
		{
			if (IsMove(tile[row - 1][col]))
			{
				AstarNode *add = new AstarNode();;
				add->point.x = tile[row - 1][col].position.x;
				add->point.y = tile[row - 1][col].position.y;
				add->row = row - 1;
				add->col = col;
				add->count = node->count + 1;
				add->value = ExpectValue(row - 1, col, add->count);
				node->Node_left = add;
			}
		}

		if (row + 1 >= 0 && dir != LEFT && node->Node_right == nullptr)
		{
			if (IsMove(tile[row + 1][col]))
			{
				AstarNode *add = new AstarNode();;
				add->point.x = tile[row + 1][col].position.x;
				add->point.y = tile[row + 1][col].position.y;
				add->row = row + 1;
				add->col = col;
				add->count = node->count + 1;
				add->value = ExpectValue(row + 1, col, add->count);
				node->Node_right = add;
			}
		}
		if (col - 1 >= 0 && dir != DOWN && node->Node_up == nullptr)
		{
			if (IsMove(tile[row][col - 1]))
			{
				AstarNode *add = new AstarNode();;
				add->point.x = tile[row][col - 1].position.x;
				add->point.y = tile[row][col - 1].position.y;
				add->row = row;
				add->col = col - 1;
				add->count = node->count + 1;
				add->value = ExpectValue(row, col - 1, add->count);
				node->Node_up = add;
			}
		}

		if (col + 1 >= 0 && dir != UP && node->Node_down == nullptr)
		{
			if (IsMove(tile[row][col + 1]))
			{
				AstarNode *add = new AstarNode();;
				add->point.x = tile[row][col + 1].position.x;
				add->point.y = tile[row][col + 1].position.y;
				add->row = row;
				add->col = col + 1;
				add->count = node->count + 1;
				add->value = ExpectValue(row, col + 1, add->count);
				node->Node_down = add;
			}
		}

		CustomPoint* add = new CustomPoint();
		add->point = node->point;
		add->count = node->count;
		add->row = node->row;
		add->col = node->col;
		erasepath(add->count);
		vPath.push_back(add);

		int minrowdif = endRow - node->row;
		int mincoldif = endCol - node->col;

		if (minrowdif < 0) minrowdif = minrowdif * -1;
		if (mincoldif < 0) mincoldif = mincoldif * -1;

		if (minrowdif + mincoldif == 1)
		{
			PathFindEnd = true;
		}

		if (NextNodeCheck(node->Node_left))
		{
			PathFind(tile, node->Node_left->row, node->Node_left->col, node->Node_left, LEFT);
			check = true;
		}
		if (PathFindEnd)return;
		if (NextNodeCheck(node->Node_right))
		{
			PathFind(tile, node->Node_right->row, node->Node_right->col, node->Node_right, RIGHT);
			check = true;
		}
		if (PathFindEnd)return;
		if (NextNodeCheck(node->Node_down))
		{
			PathFind(tile, node->Node_down->row, node->Node_down->col, node->Node_down, DOWN);
			check = true;
		}
		if (PathFindEnd)return;
		if (NextNodeCheck(node->Node_up))
		{
			PathFind(tile, node->Node_up->row, node->Node_up->col, node->Node_up, UP);
			check = true;
		}
		if (PathFindEnd)return;

		if (check == false)
		{
			node->addvalue = node->addvalue + 10000;
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

	bool NextNodeCheck(AstarNode* node)
	{
		if (node != nullptr && minvalue >= node->value + node->addvalue) return true;
		return false;
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

		if (header == nullptr)
		{
			AstarNode *add = new AstarNode();;
			add->point.x = tile[startRow][startCol].position.x;
			add->point.y = tile[startRow][startCol].position.y;
			add->row = startRow;
			add->col = startCol;
			add->count = 0;
			add->value = ExpectValue(startRow, startCol,add->count);
			header = add;
			minvalue = add->value;
		}


		PathFind(tile, header->row, header->col, header, -1);



		
	}

};

