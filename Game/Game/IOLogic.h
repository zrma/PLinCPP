#pragma once
#include <vector>
#include <string>
class CIOLogic
{
public:
	CIOLogic(void);
	~CIOLogic(void);

	void		InputPrompt(std::string inputPrompt);
	void		OutputPrompt();

private:
	std::vector<std::string>	m_CommentPromptVector;
};

