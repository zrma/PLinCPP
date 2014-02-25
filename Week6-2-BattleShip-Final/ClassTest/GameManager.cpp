#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include <windows.h>

#define MAX_TURN	MAP_SIZE * MAP_SIZE
#define RUNNING_TIME		10

CGameManager* CGameManager::m_pInstance = NULL;

CGameManager::CGameManager(void)
{
}


CGameManager::~CGameManager(void)
{
}

void CGameManager::Run()
{
	CPlayer*	pAttacker	= new CPlayer();
	CPlayer*	pDefender	= new CPlayer();
	
	int totalTurn	= 0;
	int worstCase	= 0;
	int	bestCase	= MAX_TURN;

	int	runningTime	= RUNNING_TIME;
	char string[255]	= {0, };

	sprintf_s(string, "Press ");
	CUIManager::GetInstance()->BroadCast(string, false);
	sprintf_s(string, "[ENTER]");
	CUIManager::GetInstance()->BroadCast(string, true, 7);
	getchar();
	CUIManager::GetInstance()->Clear();

	for(int i = 0; i < runningTime; ++i)
	{
		int turn = 0;

		pDefender->SetPositionRandom();

		turn = pAttacker->StartAttack(pDefender);
		totalTurn += turn;

		if(worstCase < turn)
		{
			worstCase = turn;
#ifndef TEST_FLAG
			sprintf_s(string, "    -> Worst Case! Turn : %d", turn);
			CUIManager::GetInstance()->BroadCast(string);
#endif
		}
		if(bestCase > turn)
		{
			bestCase = turn;
#ifndef TEST_FLAG
			sprintf_s(string, "    -> Best  Case! Turn : %d", turn);
			CUIManager::GetInstance()->BroadCast(string);
#endif
		}

	}

	sprintf_s(string, "\n    %d Cycle Average Turn : %d \n", runningTime, (int) (totalTurn / runningTime));
	CUIManager::GetInstance()->BroadCast(string);

	sprintf_s(string, "    Best Case : %d, Worst Case : %d", bestCase, worstCase);
	CUIManager::GetInstance()->BroadCast(string);

	delete pAttacker;
	delete pDefender;
}

CGameManager* CGameManager::GetInstance()
{
	if(m_pInstance)
		return m_pInstance;
	else
	{
		m_pInstance = new CGameManager();
		return m_pInstance;
	}
}

void CGameManager::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
