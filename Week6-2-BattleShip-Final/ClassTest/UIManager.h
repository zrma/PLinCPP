#pragma once
#include "OutputUI.h"
#include "SoundUI.h"

class CUIManager
{
public:
	CUIManager(void);
	~CUIManager(void);

	void	BroadCast(char* message, bool newLine = true, int broadType = 0);
	void	Clear();
	void	Sound(int soundType = 0);

	// 싱글톤 디자인
	// static 메소드는 객체 생성이 없어도 호출 가능함.
	// static 메소드는 static 멤버 변수만 접근 가능함.

	// 싱글톤 메소드
public:
	static CUIManager*	GetInstance();
	static void			ReleaseInstance();

private:
	// 싱글톤 객체
	static CUIManager*	m_pInstance;

private:
	COutputUI	m_OutputUI;
	CSoundUI	m_SoundUI;
};

