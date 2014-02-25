#include "stdafx.h"
#include "UIManager.h"

CUIManager* CUIManager::m_pInstance = NULL;
// 싱글톤 -> 헤더에서 선언 한 것의 초기화를 이곳에서.

CUIManager::CUIManager(void)
{
}


CUIManager::~CUIManager(void)
{
}

CUIManager* CUIManager::GetInstance()
{
	if(m_pInstance)
		return m_pInstance;
	else
	{
		m_pInstance = new CUIManager();
		return m_pInstance;
	}
}

void CUIManager::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CUIManager::BroadCast( char* message, bool newLine /*= true*/, int broadType /*= 0*/)
{
	switch (broadType)
	{
	case 0:
		m_OutputUI.SetColor(BLACK, GRAY);
		break;
	case 1:
		m_OutputUI.SetColor(DARK_GRAY, GRAY);
		break;
	case 2:
		m_OutputUI.SetColor(RED, GRAY);
		break;
	case 3:
		m_OutputUI.SetColor(BLUE, GRAY);
		break;
	case 4:
		m_OutputUI.SetColor(VIOLET, GRAY);
		break;
	case 5:
		m_OutputUI.SetColor(DARK_GREEN, GRAY);
		break;
	case 6:
		m_OutputUI.SetColor(DARK_SKY_BLUE, GREEN);
		break;
	case 7:
		m_OutputUI.SetColor(BLACK, WHITE);
		break;
	default:
		break;
	}
	m_OutputUI.BroadCast(message, newLine);
}

void CUIManager::Clear()
{
	m_OutputUI.Clear();
}

void CUIManager::Sound( int soundType /*= 0*/ )
{
	switch (soundType)
	{
	case 1:
		m_SoundUI.Sound(A);
		break;
	case 2:
		m_SoundUI.Sound(B);
		break;
	case 3:
		m_SoundUI.Sound(C);
		break;
	case 4:
		m_SoundUI.Sound(D);
		break;
	default:
		break;
	}
}
