#pragma once

#include "CommonFeature.h"
#include <time.h>
//- Type 타입에 따라 형변환후에 드로우 때림
//- Draw
//- AnimatinKeyFrame
//- AnimatinKeyEnd
//- DrawPath

class CustomObject
{
protected:
	int m_iType;	// 오브젝트 종류
	int m_iAnimationKeyFrame;	// 애니메이션 키 프레임
	int m_iAnimationEndFrame = -1;  // 애니메이션 종료 프레임 -1 일경우에는 애니메이션이 존재 하지 않는다.
	TCHAR* m_tDrawPath;			// 이미지 경로
	vector<TCHAR*> m_vAnimationPath; // 애니메이션 경로

	int m_iXpos;
	int m_iYpos;
	int m_iWidth;
	int m_iHeight;

	int m_SCRXpos;
	int m_SCRYpos;
	int m_SCRWidth;
	int m_SCRHeight;

	double FrameTime = 0;
	double PreTime = 0;
public:

	int GetType() { return m_iType; }
	int GetXpos() { return m_iXpos; }
	int GetYpos() { return m_iYpos; }
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	int GetSCRXpos() { return m_SCRXpos; }
	int GetSCRYpos() { return m_SCRYpos; }
	int GetSCRWidth() { return m_SCRWidth; }
	int GetSCRHeight() { return m_SCRHeight; }

	void AnimationKeyFrameAdd()
	{
		if (m_iAnimationEndFrame == -1) return;
		
		if (clock() - PreTime > FrameTime)
		{
			PreTime = clock();
			m_iAnimationKeyFrame++;
		}
		
		if (m_iAnimationKeyFrame == m_iAnimationEndFrame) m_iAnimationKeyFrame = 0;
		return;
	}
	TCHAR* GetAnimationPath()
	{
		if (m_iAnimationEndFrame == -1) return m_tDrawPath;

		TCHAR* result = m_vAnimationPath[m_iAnimationKeyFrame];

		AnimationKeyFrameAdd();

		return result;
	}

	virtual void Process() {};
};

