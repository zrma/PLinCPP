#include "stdafx.h"
#include "Player.h"
#include <iostream>


CPlayer::CPlayer(void)
{
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::DisplayStatus()
{
	std::cout << "[HP:" << m_CreatureInfo.GetGageCurrent(HITPOINT)
		<< "/" << m_CreatureInfo.GetGageMax(HITPOINT) << "] ";
}

void CPlayer::InitialzeCharacter()
{
	std::string	inputString;
	std::string name;
	bool		isComplete = false;

	while(!isComplete)
	{
		std::cout << "당신의 이름은 무엇입니까? ";
		std::cin >> inputString;
		name = inputString;

		std::cout << "당신의 이름이 " << inputString << "이 맞습니까? (예/아니오) ";
		std::cin >> inputString;

		if(inputString == "예")
			isComplete = true;
	}

	m_CreatureInfo.SetName(name);
	m_CreatureInfo.SetGageCurrent(HITPOINT, 100);
	m_CreatureInfo.SetGageMax(HITPOINT, 100);

	std::cout << "반갑습니다. [" << m_CreatureInfo.GetName() << "]님." << std::endl;
}
