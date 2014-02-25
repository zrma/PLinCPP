#pragma once
#include <string>
class CCharacter
{
public:
	CCharacter(void);
	virtual ~CCharacter(void);

	virtual void	Dead() = 0;
	void			SetName(std::string name) { m_Name = name; }
	std::string		GetName() { return m_Name; }
	void			SetHP(int hpCurrent) { m_HPCurrent = hpCurrent; }
	int				GetHP() { return m_HPCurrent; }

private:
	std::string	m_Name;
	int			m_HPCurrent;
};

