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
		std::cout << "����� �̸��� �����Դϱ�? ";
		std::cin >> inputString;
		name = inputString;

		std::cout << "����� �̸��� " << inputString << "�� �½��ϱ�? (��/�ƴϿ�) ";
		std::cin >> inputString;

		if(inputString == "��")
			isComplete = true;
	}

	m_CreatureInfo.SetName(name);
	m_CreatureInfo.SetGageCurrent(HITPOINT, 100);
	m_CreatureInfo.SetGageMax(HITPOINT, 100);

	std::cout << "�ݰ����ϴ�. [" << m_CreatureInfo.GetName() << "]��." << std::endl;
}
