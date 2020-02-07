#pragma once

#include <Windows.h>

class BaseTile
{
protected:
	bool m_isDestory = false;	//�ı� ���� ����
	bool m_isMove = true;		// �̵� ���� ����
	bool m_isFloor = false;		// �ٴ��̳�
	bool m_isTop = false;		// ��ũ���� ���� �׷����� ���̳�
	bool m_isLife = false;		// ������ 
	int m_witdh;		// ��� ũ�� ����
	int m_height;		// ��� ũ�� ����
	int m_scrwitdh;		// ���� ��� ����
	int m_scrheight;	// ���� ��� ����
	TCHAR* m_tDrawPath = nullptr;	// �̹��� ���
	

public:
	BaseTile() {};
	~BaseTile() {};

	TCHAR* GetImagePath()
	{
		return m_tDrawPath;
	}

	void SetImagePath(TCHAR* value)
	{
		m_tDrawPath = value;
	}

	int GetWidth() { return m_witdh; }
	int GetHeight() { return m_height; }
	int GetScrWidth() { return m_scrwitdh; }
	int GetScrHeight() { return m_scrheight; }
	bool GetIsDestory() { return m_isDestory; }
	bool GetIsMove() { return m_isMove; }
	bool GetIsFloor() { return m_isFloor; }
	bool GetIsTop() { return m_isTop; }
	bool GetIsLife() { return m_isLife; }

	void SetWidth(int value) { m_witdh = value; }
	void SetHeight(int value) { m_height = value; }
	void SetScrWidth(int value) { m_scrwitdh = value; }
	void SetScrHeight(int value) { m_scrheight = value; }
	void SetIsDestory(bool value) { m_isDestory = value; }
	void SetIsMove(bool value) { m_isMove = value; }
	void SetIsFloor(bool value) { m_isFloor = value; }
	void SetIsTop(bool value) { m_isTop = value; }
	void SetIsLife(bool value) { m_isLife = value; }

	BaseTile(TCHAR* path)
	{
		m_tDrawPath = path;

		HBITMAP BitMap = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP bit;

		GetObject(BitMap, sizeof(BITMAP), &bit);

		m_witdh = bit.bmWidth;
		m_height = bit.bmHeight;

		m_scrwitdh = bit.bmWidth;
		m_scrheight = bit.bmHeight;
	}
};

