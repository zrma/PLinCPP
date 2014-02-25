#pragma once
#include "UIManager.h"

#define TEST_FLAG

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	void		Run();

public:
	static CGameManager*	GetInstance();
	static void						ReleaseInstance();

protected:
	// �̱��� ��ü
	static CGameManager*	m_pInstance;

private:
	int		m_ShipDestroyCount;
};

