#pragma once

#include "CommonFeature.h"
#include <time.h>
//- Type Ÿ�Կ� ���� ����ȯ�Ŀ� ��ο� ����
//- Draw
//- AnimatinKeyFrame
//- AnimatinKeyEnd
//- DrawPath

class CustomObject
{
protected:
	int m_iType;	// ������Ʈ ����
	int m_iAnimationKeyFrame;	// �ִϸ��̼� Ű ������
	int m_iAnimationEndFrame = -1;  // �ִϸ��̼� ���� ������ -1 �ϰ�쿡�� �ִϸ��̼��� ���� ���� �ʴ´�.
	TCHAR* m_tDrawPath;			// �̹��� ���
	vector<TCHAR*> m_vAnimationPath; // �ִϸ��̼� ���

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

