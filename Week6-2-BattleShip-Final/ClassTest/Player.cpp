#include "stdafx.h"
#include "Player.h"

// 헤더파일 커플링 제거
#include "Aircraft.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"

#include "WellRandom.h"
#include "GameManager.h"

CPlayer::CPlayer(void)
{
	CAircraft*		pAircraft		= new CAircraft();
	CBattleship*	pBattleship	= new CBattleship();
	CCruiser*		pCruiser_1		= new CCruiser();
	CCruiser*		pCruiser_2		= new CCruiser();
	CDestroyer*	pDestroyer_1	= new CDestroyer();
	CDestroyer*	pDestroyer_2	= new CDestroyer();

	m_Ships[0] = pAircraft;
	m_Ships[1] = pBattleship;
	m_Ships[2] = pCruiser_1;
	m_Ships[3] = pCruiser_2;
	m_Ships[4] = pDestroyer_1;
	m_Ships[5] = pDestroyer_2;

	m_LeftShips = sizeof(m_Ships) / sizeof(m_Ships[0]);
}

CPlayer::~CPlayer(void)
{
	for(int i = 0; i < sizeof(m_Ships) / sizeof(m_Ships[0]); ++i)
	{
		if(m_Ships[i])
		{
			delete(m_Ships[i]);
			m_Ships[i] = NULL;
		}
	}
}

HitResult CPlayer::HitCheck(Position hitPos)
{
	HitResult tempResult = MISS;

	for (int i = 0; i < sizeof(m_Ships)/sizeof(m_Ships[0]); i++)
	{
		tempResult = m_Ships[i]->HitCheck(hitPos);

		if(tempResult != HIT && tempResult != MISS && !m_Ships[i]->IsDead())
				--m_LeftShips;
			
		if(tempResult != MISS)
			return tempResult;
	}

	return tempResult;
}

void CPlayer::SetPositionRandom()
{
	m_LeftShips = sizeof(m_Ships) / sizeof(m_Ships[0]);
	m_MyMap.InitMapInfo(MI_ShipType);

	int		nPosX, nPosY;
	char	cPosX, cPosY;
	bool	isPossible;
	int		nPositionedShip = 0;
	int		shipSize = 0;

	MapInfo		mapInfo;
	VerticalType	isVertical = VERTICAL;


	while(nPositionedShip < m_LeftShips)
	{
		isPossible = true;
		shipSize = m_Ships[nPositionedShip]->GetHPMAX();
		nPosX = CWellRandom::GetInstance()->WellRand(MAP_SIZE);
		nPosY = CWellRandom::GetInstance()->WellRand(MAP_SIZE);

		(CWellRandom::GetInstance()->WellRand(2) == 0) ? isVertical = VERTICAL : isVertical = HORIZON; 

		for(int i = 0; i < shipSize; ++i)
		{
			cPosX = nPosX + 'A' + ((isVertical == VERTICAL) ?  i : 0);
			cPosY = nPosY + '1' + ((isVertical == HORIZON) ? i : 0);
			if(m_MyMap.GetMapInfo(cPosX, cPosY, MI_ShipType).value.shipType != WATER)
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

			mapInfo.type = MI_ShipType;
			mapInfo.value.shipType = m_Ships[nPositionedShip]->GetType();
			m_MyMap.SetMapInfo(cPosX, cPosY, mapInfo);
			
			m_Ships[nPositionedShip]->AddPosition(cPosX, cPosY);
		}
		++nPositionedShip;
	}
}

void CPlayer::InitGuessShipState()
{
	for(int i = 0; i < sizeof(m_Ships) / sizeof(m_Ships[0]); ++i)
	{
		m_Ships[i]->SetHPCURRENT(m_Ships[i]->GetHPMAX());
	}
}

int CPlayer::StartAttack( CPlayer* pDefender )
{
	int			destroyCount	= 0;
	int			hitCount		= 0;
	int			turn				= 0;
	int			maxTurn		= MAP_SIZE * MAP_SIZE;
	
	Position		attackPosition = {0, };
	HitResult	result = MISS;
	MapInfo	mapInfo;
	char			string[255] = {0, };

	m_MyMap.InitMapInfo(MI_All);
	InitGuessShipState();

	while(turn < maxTurn)
	{
		mapInfo.Init();
		++turn;

		m_MyMap.InitMapInfo(MI_Probability);

#ifdef TEST_FLAG
		// 공격 결과 출력
		sprintf_s(string, " ");
		CUIManager::GetInstance()->BroadCast(string);
		m_MyMap.DisplayMap(MI_HitResult);
#endif
		// 확률 계산
		CalculateProbability();
		
		// 최대값 찾기
		attackPosition = GetBestPosition();
		result = pDefender->HitCheck(attackPosition);

#ifdef TEST_FLAG
		sprintf_s(string, "    Attack Position : ( %c , %c ) ", attackPosition.x, attackPosition.y);
		CUIManager::GetInstance()->BroadCast(string);
#endif

		switch (result)
		{
		case MISS:
#ifdef TEST_FLAG
			sprintf_s(string, "    Miss! - Turn : %d", turn);
			CUIManager::GetInstance()->BroadCast(string);
			sprintf_s(string, "       - Hit : %d, Destroy : %d", hitCount, destroyCount);
			CUIManager::GetInstance()->BroadCast(string);
#endif
			mapInfo.type = MI_HitResult;
			mapInfo.value.hitResult = MISS;
			m_MyMap.SetMapInfo(attackPosition, mapInfo);

			break;
		case HIT:
			++hitCount;
#ifdef TEST_FLAG
			sprintf_s(string, "    Hit ! - Turn : %d", turn);
			CUIManager::GetInstance()->BroadCast(string);
			sprintf_s(string, "       - Hit : %d, Destroy : %d", hitCount, destroyCount);
			CUIManager::GetInstance()->BroadCast(string);
#endif	
			mapInfo.type = MI_HitResult;
			mapInfo.value.hitResult = HIT;
			m_MyMap.SetMapInfo(attackPosition, mapInfo);

			break;
		case DESTROY_AIRCRAFT:
		case DESTROY_BATTLESHIP:
		case DESTROY_CRUISER:
		case DESTROY_DESTROYER:
		case DESTROY_SUBMARINE:

			mapInfo.type = MI_HitResult;
			mapInfo.value.hitResult = HIT;
			m_MyMap.SetMapInfo(attackPosition, mapInfo);

#ifdef TEST_FLAG
			sprintf_s(string, "    Destroy!!! - Turn : %d", turn);
			CUIManager::GetInstance()->BroadCast(string);
			sprintf_s(string, "      - Hit : %d, Destroy : %d", hitCount, destroyCount);
			CUIManager::GetInstance()->BroadCast(string);
#endif

			// 터진 배 추측
			GuessDestroyedShip(result, attackPosition);
			
			++hitCount;
			++destroyCount;
			if(destroyCount >= sizeof(m_Ships) / sizeof(m_Ships[0]))
			{
#ifdef TEST_FLAG
				m_MyMap.DisplayMap(MI_Probability, attackPosition.x, attackPosition.y);
				pDefender->m_MyMap.DisplayMap(MI_ShipType);
#endif
				sprintf_s(string, "      Victory !!! Turn : %d", turn);
				CUIManager::GetInstance()->BroadCast(string);
#ifdef TEST_FLAG
			
				CUIManager::GetInstance()->Sound(4);
				Sleep(3000);
				CUIManager::GetInstance()->Clear();
#endif
				return turn;
			}
			break;
		default:
			// 이곳은 도달하면 안 됨.
#ifdef TEST_FLAG
			sprintf_s(string, "    Do not reach here! - Destroy error");
			CUIManager::GetInstance()->BroadCast(string);
#endif
			break;
		}

#ifdef TEST_FLAG
		// 공격 결과 출력
		m_MyMap.DisplayMap(MI_Probability, attackPosition.x, attackPosition.y);
		pDefender->m_MyMap.DisplayMap(MI_ShipType);

		switch(result)
		{
		case MISS:
			CUIManager::GetInstance()->Sound(1);
			break;
		case HIT:
			CUIManager::GetInstance()->Sound(2);
			break;
		case DESTROY_AIRCRAFT:
		case DESTROY_BATTLESHIP:
		case DESTROY_CRUISER:
		case DESTROY_DESTROYER:
		case DESTROY_SUBMARINE:
			CUIManager::GetInstance()->Sound(3);
			break;
		default:
			break;
		}

		Sleep(500);
		CUIManager::GetInstance()->Clear();
#endif
	}

	// Error
	return	-9999;
}

void CPlayer::CalculateProbability()
{
	MapInfo mapInfo;
	Position pos;

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		for(int j = 0; j < MAP_SIZE; ++j)
		{
			pos.x = i + 'A';
			pos.y = j + '1';

			if(m_MyMap.GetMapInfo(pos, MI_HitResult).value.hitResult == MISS || 
					m_MyMap.GetMapInfo(pos, MI_HitResult).value.hitResult == DESTROY)
			{
				mapInfo.type = MI_Probability;
				mapInfo.value.probability = 0;
				m_MyMap.SetMapInfo(pos, mapInfo);
			}
			else if(m_MyMap.GetMapInfo(pos, MI_HitResult).value.hitResult == HIT)
			{
				mapInfo.type = MI_Probability;
				mapInfo.value.probability = 0;
				m_MyMap.SetMapInfo(pos, mapInfo);

				int nArrayX[] = {0, 0, -1, 1};
				int nArrayY[] = {-1, 1, 0, 0};

				for(int k = 0; k < sizeof(nArrayX)/sizeof(nArrayX[0]); ++k)
				{
					pos.x = i + nArrayX[k] + 'A';
					pos.y = j + nArrayY[k] + '1';
					
					if(m_MyMap.IsValid(pos) == false || m_MyMap.GetMapInfo(pos, MI_HitResult).value.hitResult != UNKNOWN)
						continue;

					mapInfo = m_MyMap.GetMapInfo(i + 'A', j + '1', MI_Probability);
					mapInfo.value.probability += 100;
					m_MyMap.SetMapInfo(pos, mapInfo);

					if(m_MyMap.GetMapInfo(i - nArrayX[k] + 'A', j - nArrayY[k] + '1', MI_HitResult).value.hitResult == HIT)
					{
						mapInfo = m_MyMap.GetMapInfo(pos, MI_Probability);
						mapInfo.value.probability += 100;
						m_MyMap.SetMapInfo(pos, mapInfo);
					}

					if(m_MyMap.GetMapInfo(i - nArrayX[k] * 2 + 'A', j - nArrayY[k] * 2 + '1', MI_HitResult).value.hitResult == HIT)
					{
						pos.x = i + nArrayX[k] + 'A';
						pos.y = j + nArrayY[k] + '1';

						mapInfo = m_MyMap.GetMapInfo(pos, MI_Probability);
						mapInfo.value.probability += 100;
						m_MyMap.SetMapInfo(pos, mapInfo);
					}
				}
			}
			else
			{
				Position pos;
				pos.x = i + 'A';
				pos.y = j + '1';

				mapInfo.type = MI_Probability;
				mapInfo.value.probability = m_MyMap.GetMapInfo(pos, MI_Probability).value.probability + GetProbabilityThisPosition(pos);
				m_MyMap.SetMapInfo(pos, mapInfo);
			}
		}
	}
}

int CPlayer::GetProbabilityThisPosition(Position pos)
{
	int	probability	= 0;
	int shipSize	= 0;

	for(int i = 0; i < (sizeof(m_Ships) / sizeof(m_Ships[0])); ++i)
	{
		if(m_Ships[i]->GetHPCURRENT() != 0)
		{
			shipSize = m_Ships[i]->GetHPMAX();
			probability += GetProbabilitySurroundShip(pos, shipSize);
		}
	}

	return probability;
}

int CPlayer::GetProbabilitySurroundShip(Position pos, int shipSize)
{
	int				probability = 0;
	bool			isPossible	= true;
	MapInfo	mapInfo;

	for(int	i = 1 - shipSize; i <= 0; ++i)
	{
		if(m_MyMap.IsValid(pos.x + i, pos.y) == true && 
			m_MyMap.IsValid(pos.x + i + shipSize - 1, pos.y) == true)
		{
			isPossible = true;
			for(int j = 0; j < shipSize; ++j)
			{
				if(m_MyMap.GetMapInfo(pos.x + i + j, pos.y, MI_HitResult).value.hitResult != UNKNOWN)
				{
					isPossible = false;
					break;
				}
			}

			if(isPossible == true)
				probability += shipSize;
		}

		if(m_MyMap.IsValid(pos.x, pos.y + i) == true && 
			m_MyMap.IsValid(pos.x, pos.y + i + shipSize - 1) == true)
		{
			isPossible = true;
			for(int j = 0; j < shipSize; ++j)
			{
				if(m_MyMap.GetMapInfo(pos.x, pos.y + i + j, MI_HitResult).value.hitResult != UNKNOWN)
				{
					isPossible = false;
					break;
				}
			}

			if(isPossible == true)
				probability += shipSize;
		}
	}

	return probability;
}

Position CPlayer::GetBestPosition()
{
	Position	bestPos = {0, };
	int			bestProbability = 0;

	for(int i = 0; i < MAP_SIZE; ++i)
		for(int j = 0; j < MAP_SIZE; ++j)
			if(bestProbability < m_MyMap.GetMapInfo(i + 'A', j + '1', MI_Probability).value.probability)
			{
				bestProbability = m_MyMap.GetMapInfo(i + 'A', j + '1', MI_Probability).value.probability;
				bestPos.x = i + 'A';
				bestPos.y = j + '1';
			}

			return bestPos;
}

void CPlayer::GuessDestroyedShip(HitResult result, Position pos )
{
	int				direction = -1;
	int				shipSize = 0;
	MapInfo	mapInfo;
	ShipType	shipType = NONE;

	switch (result)
	{
	case DESTROY_AIRCRAFT:
		shipType = AIRCRAFT;
		break;
	case DESTROY_BATTLESHIP:
		shipType = BATTLESHIP;
		break;
	case DESTROY_CRUISER:
		shipType = CRUISER;
		break;
	case DESTROY_DESTROYER:
		shipType = DESTROYER;
		break;
	case DESTROY_SUBMARINE:
		shipType = SUBMARINE;
		break;
	default:
		break;
	}

	for(int i = 0; i < sizeof(m_Ships) / sizeof(m_Ships[0]); ++i)
		if(m_Ships[i]->GetType() == shipType && m_Ships[i]->GetHPCURRENT() != 0)
		{
			shipSize = m_Ships[i]->GetHPMAX();
			m_Ships[i]->SetHPCURRENT(0);
			break;
		}

		int nArrayX[] = {0, 0, -1, 1};
		int nArrayY[] = {-1, 1, 0, 0};

		int count = 0;

		for(int i = 0; i < sizeof(nArrayX) / sizeof(nArrayX[0]); ++i) 
		{
			count = 0;

			for(int j = 0; ; ++j) 
			{
					if(m_MyMap.GetMapInfo(pos.x + nArrayX[i] * j, pos.y + nArrayY[i] * j, MI_HitResult).value.hitResult != HIT || 
					m_MyMap.IsValid(pos.x + nArrayX[i] * j, pos.y + nArrayY[i] * j) == false || 
					count >= shipSize ) 
					break;

				++count;
			}

			if( count == shipSize ) 
			{
				direction = i;
				break;
			}
		}

		if(direction != -1) 
			for(int i = 0; i < shipSize; ++i) 
			{
				mapInfo.type = MI_HitResult;
				mapInfo.value.hitResult = DESTROY;
				m_MyMap.SetMapInfo(pos.x + nArrayX[direction] * i, pos.y + nArrayY[direction] * i, mapInfo);
			}
}
