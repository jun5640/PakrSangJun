#pragma once

#include <Windows.h>

class BaseTile
{
protected:
	bool m_isDestory = false;	//파괴 가능 유무
	bool m_isMove = true;		// 이동 가능 유무
	bool m_isFloor = false;		// 바닥이냐
	bool m_isTop = false;		// 탱크보다 위에 그려지는 아이냐
	bool m_isLife = false;		// 라이프 
	int m_witdh;		// 출력 크기 넓이
	int m_height;		// 출력 크기 높이
	int m_scrwitdh;		// 원본 출력 넓이
	int m_scrheight;	// 원본 출력 높이
	TCHAR* m_tDrawPath = nullptr;	// 이미지 경로
	

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

