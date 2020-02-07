#pragma once

#include <Windows.h>
#include <vector>

using namespace std;

class BasePlayer
{
protected:
	POINT position;
	vector<TCHAR*> m_vAnimationPath; // 애니메이션 경로
	int m_iAnimationKeyFrame;	// 애니메이션 키 프레임
	int m_iAnimationEndFrame = -1;  // 애니메이션 종료 프레임 -1 일경우에는 애니메이션이 존재 하지 않는다.

	int m_iWidth;
	int m_iHeight;

	int m_SCRWidth;
	int m_SCRHeight;
public:

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	int GetSCRWidth() { return m_SCRWidth; }
	int GetSCRHeight() { return m_SCRHeight; }

	POINT GetPosition() { return position; }

	void SetDie()
	{
		m_vAnimationPath.clear();

		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_00.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_01.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_02.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_03.bmp"));
		m_vAnimationPath.push_back((TCHAR*)TEXT("BattleCity/explosion_04.bmp"));

		m_iAnimationEndFrame = 5;
		m_iAnimationKeyFrame = 0;
	}

	void AnimationKeyFrameAdd()
	{
		if (m_iAnimationEndFrame == -1) return;

		//if (clock() - PreTime > FrameTime)
		//{
		//	PreTime = clock();
			m_iAnimationKeyFrame++;
		//}

		if (m_iAnimationKeyFrame == m_iAnimationEndFrame) m_iAnimationKeyFrame = 0;
		return;
	}

	TCHAR* GetAnimationPath()
	{
		//if (m_iAnimationEndFrame == -1 || !m_IsPlayAnimaion) return m_tDrawPath;

		TCHAR* result = m_vAnimationPath[m_iAnimationKeyFrame];

		AnimationKeyFrameAdd();

		return result;
	}

	virtual void Fire()
	{

	}
};

