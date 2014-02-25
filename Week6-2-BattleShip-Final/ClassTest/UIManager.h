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

	// �̱��� ������
	// static �޼ҵ�� ��ü ������ ��� ȣ�� ������.
	// static �޼ҵ�� static ��� ������ ���� ������.

	// �̱��� �޼ҵ�
public:
	static CUIManager*	GetInstance();
	static void			ReleaseInstance();

private:
	// �̱��� ��ü
	static CUIManager*	m_pInstance;

private:
	COutputUI	m_OutputUI;
	CSoundUI	m_SoundUI;
};

