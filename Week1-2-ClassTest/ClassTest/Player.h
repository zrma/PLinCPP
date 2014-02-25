#pragma once
#include <string>
class cPlayer
{
public:
	cPlayer(void);
	~cPlayer(void);

	int type;
	bool turn;
	std::string name;

	int inputLoc();
};

