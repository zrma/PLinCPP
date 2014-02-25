#pragma once
class cLogic
{
public:
	cLogic(void);
	~cLogic(void);

	int turn;
	unsigned long run_time;
	int ship_1p_survival;
	int ship_2p_survival;

	int checkTime();
	int checkWin();
	int printStat();
};

