#include "stdafx.h"
#include "Player.h"

// 헤더파일 커플링 제거
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"
#include <iostream>

#include "WellRandom.h"

//#define TEST_FLAG

CPlayer::CPlayer(void)
{
	CAircraft*		pAircraft		= new CAircraft();
	CBattleship*	pBattleship		= new CBattleship();
	CCruiser*		pCruiser_1		= new CCruiser();
	CCruiser*		pCruiser_2		= new CCruiser();
	CDestroyer*		pDestroyer_1	= new CDestroyer();
	CDestroyer*		pDestroyer_2	= new CDestroyer();
//	CSubmarine*		pSubmarine_1	= new CSubmarine();
//	CSubmarine*		pSubmarine_2	= new CSubmarine();

	m_Ships[0] = pAircraft;
	m_Ships[1] = pBattleship;
	m_Ships[2] = pCruiser_1;
	m_Ships[3] = pCruiser_2;
	m_Ships[4] = pDestroyer_1;
	m_Ships[5] = pDestroyer_2;
//	m_Ships[6] = pSubmarine_2;

	m_LeftShips = sizeof(m_Ships) / sizeof(CShip*);
	InitWELLRNG();
}

CPlayer::~CPlayer(void)
{
	for(int i = 0; i < sizeof(m_Ships) / sizeof(CShip*); ++i)
	{
		if(m_Ships[i])
		{
			delete(m_Ships[i]);
			m_Ships[i] = NULL;
		}
	}
}

void CPlayer::SetPosition()
{

	m_Ships[0]->AddPosition('B','8');
	m_Ships[0]->AddPosition('C','8');
	m_Ships[0]->AddPosition('D','8');
	m_Ships[0]->AddPosition('E','8');
	m_Ships[0]->AddPosition('F','8');

	m_Ships[1]->AddPosition('A','4');
	m_Ships[1]->AddPosition('A','5');
	m_Ships[1]->AddPosition('A','6');
	m_Ships[1]->AddPosition('A','7');

	m_Ships[2]->AddPosition('F','4');
	m_Ships[2]->AddPosition('F','5');
	m_Ships[2]->AddPosition('F','6');

	m_Ships[3]->AddPosition('H','6');
	m_Ships[3]->AddPosition('H','7');

	m_Ships[4]->AddPosition('C','1');
	m_Ships[4]->AddPosition('C','2');

	m_Ships[5]->AddPosition('C','7');

	m_Ships[6]->AddPosition('G','5');

}

HitResult CPlayer::HitCheck(Position hitPos)
{
	HitResult tempResult = MISS;

	for (int i = 0; i < sizeof(m_Ships)/sizeof(CShip*); i++)
	{
		tempResult = m_Ships[i]->HitCheck(hitPos);

		if(tempResult != HIT && tempResult != MISS)
			if(!m_Ships[i]->IsDead())
				--m_LeftShips;
			
		if(tempResult != MISS)
			return tempResult;
	}

	return tempResult;
}

void CPlayer::SetPositionRandom()
{
	m_LeftShips = sizeof(m_Ships) / sizeof(CShip*);
	m_MyMap.InitMapInfo();

	int nPosX, nPosY;
	char cPosX, cPosY;
	VerticalType isVertical = VERTICAL;
	bool isPossible;

	int nPositionedShip = 0;
	int shipSize = 0;

	while(nPositionedShip < m_LeftShips)
	{
		isPossible = true;
		shipSize = m_Ships[nPositionedShip]->GetHPMAX();
		// nPosX = rand() % MAP_SIZE;
		// nPosY = rand() % MAP_SIZE;
		nPosX = WellRand(MAP_SIZE);
		nPosY = WellRand(MAP_SIZE);

		(WellRand(2) == 0) ? isVertical = VERTICAL : isVertical = HORIZON; 

		for(int i = 0; i < shipSize; ++i)
		{
			cPosX = nPosX + 'A' + ((isVertical == VERTICAL) ?  i : 0);
			cPosY = nPosY + '1' + ((isVertical == HORIZON) ? i : 0);
			if(m_MyMap.GetMapInfo(cPosX, cPosY) != WATER)
			{
				isPossible = false;
				break;
			}
		}

		if(isPossible == false)
			continue;

		for(int i = 0; i < shipSize; ++i)
		{
			cPosX = nPosX + 'A' + ((isVertical == VERTICAL) ? i : 0);
			cPosY = nPosY + '1' + ((isVertical == HORIZON) ? i : 0);
			m_MyMap.SetMapInfo(cPosX, cPosY, m_Ships[nPositionedShip]->GetType());
			m_Ships[nPositionedShip]->AddPosition(cPosX, cPosY);
		}
		++nPositionedShip;
	}
}

int CPlayer::StartAttack( CPlayer* pDefender )
{
	int			turn			= 0;
	int			destroyCount	= 0;
	int			hitCount		= 0;
	int			size			= 0;
	int			worstProbability	= 0;

	bool		isCorrect		= true;
	bool		isSurrounded	= false;

	HitResult	result			= MISS;
	Position	pos;

	char*		name[5] = { "Aircraft", "Battleship", "Cruiser", "Destroyer", "Submarine" };

	m_MyMap.ResetCount();
	m_MyMap.InitProbability();
	m_MyMap.InitMapInfo();

	for(int i = 0; i < 500; ++i)
	{
		SetPositionRandom();
		for(int i = 0; i < MAP_SIZE; ++i)
			for(int j = 0; j < MAP_SIZE; ++j)
			{
				pos.x = i + 'A';
				pos.y = j + '1';
				if(m_MyMap.GetMapInfo(pos) != WATER)
					m_MyMap.AddCount(pos);
			}
	}

	for(int i = 0; i < MAP_SIZE; ++i)
		for(int j = 0; j < MAP_SIZE; ++j)
		{
			pos.x = i + 'A';
			pos.y = j + '1';
			if(m_MyMap.GetCount(pos) < 120)
				m_MyMap.SetProbability(pos, 120);
			else
				m_MyMap.SetProbability(pos, (m_MyMap.GetCount(pos) - m_MyMap.GetCount(pos) % 10));
		}

	while(turn < 64)
	{
		++turn;

		isSurrounded = false;
		GuessBlankStatus();

		int surroundCount = 0;

		do
		{
			isSurrounded = false;
			pos = m_MyMap.GetBestProbability();

			if((m_MyMap.GetProbability(pos.x+1, pos.y) == -50 || m_MyMap.GetProbability(pos.x+1, pos.y) == -150) && 
				(m_MyMap.GetProbability(pos.x-1, pos.y) == -50 || m_MyMap.GetProbability(pos.x-1, pos.y) == -150) && 
				(m_MyMap.GetProbability(pos.x, pos.y+1) == -50 || m_MyMap.GetProbability(pos.x, pos.y+1) == -150) && 
				(m_MyMap.GetProbability(pos.x, pos.y-1) == -50 || m_MyMap.GetProbability(pos.x, pos.y-1) == -150))
			{
				m_MyMap.SetProbability(pos, -50);
				isSurrounded = true;
			}

			++surroundCount;
		} while (isSurrounded && (surroundCount + hitCount < MAP_SIZE * MAP_SIZE));

		worstProbability = m_MyMap.GetWorstProbabilityValue();

		result = pDefender->HitCheck(pos);
#ifdef TEST_FLAG
		printf_s("공격 좌표 : ( %c , %c ) \n", pos.x, pos.y);
#endif
		size = 0;

		switch (result)
		{
		case MISS:
#ifdef TEST_FLAG
			printf_s("Miss! %d턴 - Hit %d, Destroy %d \n", turn, hitCount, destroyCount);
#endif
			m_MyMap.SetProbability(pos, -50);		// NONE

			m_MyMap.SetProbability(pos.x+1, pos.y, m_MyMap.GetProbability(pos.x+1, pos.y) * 0.97 + 1);
			m_MyMap.SetProbability(pos.x-1, pos.y, m_MyMap.GetProbability(pos.x-1, pos.y) * 0.97 + 1);
			m_MyMap.SetProbability(pos.x, pos.y+1, m_MyMap.GetProbability(pos.x, pos.y+1) * 0.97 + 1);
			m_MyMap.SetProbability(pos.x, pos.y-1, m_MyMap.GetProbability(pos.x, pos.y-1) * 0.97 + 1);
			
			break;
		case HIT:
			++hitCount;
#ifdef TEST_FLAG
			printf_s("Hit!!! %d턴 - Hit %d, Destroy %d \n", turn, hitCount, destroyCount);
#endif
			m_MyMap.SetProbability(pos, -100);		// MARKING

			m_MyMap.SetProbability(pos.x+1, pos.y, m_MyMap.GetProbability(pos.x+1, pos.y) * 2);
			m_MyMap.SetProbability(pos.x-1, pos.y, m_MyMap.GetProbability(pos.x-1, pos.y) * 2);
			m_MyMap.SetProbability(pos.x, pos.y+1, m_MyMap.GetProbability(pos.x, pos.y+1) * 2);
			m_MyMap.SetProbability(pos.x, pos.y-1, m_MyMap.GetProbability(pos.x, pos.y-1) * 2);

			for(int i = 0; i < MAP_SIZE; ++i)
			{
				for(int j = 0; j < MAP_SIZE; ++j)
				{
					if(m_MyMap.GetProbability(i+'A', j+'1') > 0)
						m_MyMap.SetProbability(i+'A', j+'1', 
						m_MyMap.GetProbability(i+'A', j+'1') - (worstProbability/(64-turn)));
				}
			}

			break;
		case DESTROY_AIRCRAFT:
			++size;
		case DESTROY_BATTLESHIP:
			++size;
		case DESTROY_CRUISER:
			++size;
		case DESTROY_DESTROYER:
			++size;
		case DESTROY_SUBMARINE:
			++size;
		
			m_MyMap.SetProbability(pos, -100);
			GuessShipStatus(pos, size);

			for(int i = 0; i < MAP_SIZE; ++i)
			{
				for(int j = 0; j < MAP_SIZE; ++j)
				{
					if(m_MyMap.GetProbability(i+'A', j+'1') > 0)
						m_MyMap.SetProbability(i+'A', j+'1', 
						m_MyMap.GetProbability(i+'A', j+'1') - (worstProbability/(64-turn)));
				}
			}

			++hitCount;
			++destroyCount;
#ifdef TEST_FLAG
			printf_s("%s 파괴! %d턴 - Hit %d, Destroy %d \n", name[5-size], turn, hitCount, destroyCount);
#endif
			if(destroyCount >= 6)
			{
#ifdef TEST_FLAG
				printf_s("승리! %d턴 \n", turn);
#endif
				return turn;
			}
			break;
		case DESTROY:
			printf_s("Do not reach here! - Destroy error \n");
			getchar();
			break;
		default:
			printf_s("Do not reach here! - HitResult Switch Default \n");
			getchar();
			break;
		}

#ifdef TEST_FLAG
		m_MyMap.DisplayProbability();
		getchar();
#endif
	}

	printf_s("여기 나오면 오류 %d \n", turn);
	return	turn;
}

void CPlayer::GuessShipStatus( Position pos, int size )
{
	int		count[2]	= {-1,-1};
	int		starting[2]	= {0, };
	bool	isRight[4]	= {true, true, true, true};
	
//	printf_s("%c %c 확인하기 \n", pos.x, pos.y);

	for(int i = 0; i < size; ++i)
	{
		if(m_MyMap.GetProbability(pos.x - i, pos.y) == -100 && isRight[UP] == true)
		{
			++count[VERTICAL];
			starting[VERTICAL] = i;
		}
		else
			isRight[UP] = false;

		if(m_MyMap.GetProbability(pos.x, pos.y - i) == -100 && isRight[LEFT] == true)
		{
			++count[HORIZON];
			starting[HORIZON] = i;
		}
		else
			isRight[LEFT] = false;

		if(m_MyMap.GetProbability(pos.x + i, pos.y) == -100 && isRight[DOWN] == true)
		{
			++count[VERTICAL];
		}
		else
			isRight[DOWN] = false;

		if(m_MyMap.GetProbability(pos.x, pos.y + i) == -100 && isRight[RIGHT] == true)
		{
			++count[HORIZON];;
		}
		else
			isRight[RIGHT] = false;
	}

// 	printf_s("(%c, %c) Size = %d, starting point = V:%d, H:%d, count = V:%d, H:%d \n", 
// 			pos.x, pos.y, size, starting[VERTICAL], starting[HORIZON], count[VERTICAL], count[HORIZON]);

	for(int i = 0; i < size; ++i)
	{
		if(count[VERTICAL] == size)
		{
			m_MyMap.SetProbability(pos.x + i - starting[VERTICAL], pos.y, -150);
		}
		if(count[HORIZON] == size)
		{
			m_MyMap.SetProbability(pos.x, pos.y + i - starting[HORIZON], -150);
		}
	}

	m_MyMap.SetProbability(pos, -150);
}

void CPlayer::GuessBlankStatus()
{
	Position pos;

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			pos.x = i + 'A';
			pos.y = j + '1';
			if(m_MyMap.GetProbability(pos) > 0)
			{
				// 떨어진 두 칸 사이 확률 증가
				if((m_MyMap.GetProbability(pos.x-1, pos.y) == -100 && m_MyMap.GetProbability(pos.x+1, pos.y) == -100) ||
					(m_MyMap.GetProbability(pos.x, pos.y-1) == -100 && m_MyMap.GetProbability(pos.x, pos.y+1) == -100))
					m_MyMap.SetProbability(pos.x, pos.y , m_MyMap.GetProbability(pos) * 2);

				// 두 칸 연달아 히트면 직선 진행
				if((m_MyMap.GetProbability(pos.x-1, pos.y) == -100 && m_MyMap.GetProbability(pos.x-2, pos.y) == -100) || 
					(m_MyMap.GetProbability(pos.x+1, pos.y) == -100 && m_MyMap.GetProbability(pos.x+2, pos.y) == -100) || 
					(m_MyMap.GetProbability(pos.x, pos.y-1) == -100 && m_MyMap.GetProbability(pos.x, pos.y-2) == -100) || 
					(m_MyMap.GetProbability(pos.x, pos.y+1) == -100 && m_MyMap.GetProbability(pos.x, pos.y+2) == -100))
					m_MyMap.SetProbability(pos.x, pos.y , m_MyMap.GetProbability(pos) * 2);
			}
		}
	}
}
