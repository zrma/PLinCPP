// Overriding.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "NPC.h"
#include "Mob.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CCharacter*	partyMember[4] = {NULL, };

//	CCharacter*	hyunwoo		= new CCharacter();
	CPlayer*	moonchul	= new CPlayer();
	CNPC*		jinwoo		= new CNPC();
	CMob*		injae		= new CMob();
	CMob*		sunhyup		= new CMob();

	int ClassSize = sizeof(CCharacter);
	printf_s("CCharacter Size : %d \n", ClassSize);
	
//	CCharacter* pSehyun = new CCharacter();
	CMob* pInjae = new CMob();

//	pSehyun->Dead();
	pInjae->Dead();
	sunhyup->Dead();

	moonchul->SetName("Moon");

//	partyMember[0] = hyunwoo;
	partyMember[0] = pInjae;
	partyMember[1] = moonchul;
	partyMember[2] = jinwoo;
	partyMember[3] = injae;

	moonchul->SetName("Chul");

	printf_s("[%s] \n", partyMember[1]->GetName().c_str());
	printf_s("[%s] \n", moonchul->GetName().c_str());

	
	for(auto i = 0; i < 4; ++i)
	{
		partyMember[i]->Dead();
		free(partyMember[i]);
	}

	CPlayer	sunjin;
	sunjin.SetHP(100);

	CPlayer	sunghwan;
	sunghwan = sunjin;

	sunghwan.SetHP(1);

	printf_s("SunJin HP : %d \n", sunjin.GetHP());
	printf_s("SungHwan HP : %d \n", sunghwan.GetHP());

	CPlayer *pSunjin = new CPlayer();
	CPlayer *pSunghwan = new CPlayer();

	pSunjin->SetName("Sun-Jin");
	pSunjin->SetHP(100);
	pSunghwan->SetName("Sung-Hwan");
	pSunghwan->SetHP(-1);

	delete(pSunghwan);

	pSunghwan = pSunjin;

	printf_s("SunJin Name : %s, HP : %d \n",
		pSunjin->GetName().c_str(), pSunjin->GetHP());
	printf_s("SungHwan Name : %s, HP : %d \n",
		pSunghwan->GetName().c_str(), pSunghwan->GetHP());

	pSunjin->SetName("Sung-Hwan");

	printf_s("SunJin Name : %s, HP : %d \n",
		pSunjin->GetName().c_str(), pSunjin->GetHP());
	printf_s("SungHwan Name : %s, HP : %d \n",
		pSunghwan->GetName().c_str(), pSunghwan->GetHP());

	getchar();

	return 0;
}

