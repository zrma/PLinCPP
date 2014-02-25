#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include <windows.h>


CGameManager::CGameManager(void)
{
}


CGameManager::~CGameManager(void)
{
}

void CGameManager::Run()
{
	CPlayer*	pAttacker = new CPlayer();
	CPlayer*	pDefender = new CPlayer();

	int totalTurn	= 0;
	int worstCase	= 0;
	int	bestCase	= 64;

	int	runningTime = 1000;

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
			printf_s("Worst! %d turn \n", turn);
			pAttacker->m_MyMap.DisplayProbability();
#endif
		}
		if(bestCase > turn)
		{
			bestCase = turn;
#ifndef TEST_FLAG
			printf_s("Best!  %d turn \n", turn);
			pAttacker->m_MyMap.DisplayProbability();
#endif
		}

	}
	
	printf_s("%d회 시도 평균 턴 수 : %d \n", runningTime, (int) (totalTurn / runningTime));
	printf_s("Best Case : %d, Worst Case : %d \n", bestCase, worstCase);

	delete pAttacker;
	delete pDefender;
}
