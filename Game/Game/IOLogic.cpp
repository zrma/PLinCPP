#include "stdafx.h"
#include "IOLogic.h"


CIOLogic::CIOLogic(void)
{
}


CIOLogic::~CIOLogic(void)
{
}

void CIOLogic::InputPrompt( std::string inputPrompt )
{
	m_CommentPromptVector.push_back(inputPrompt);
}

void CIOLogic::OutputPrompt()
{
	while(m_CommentPromptVector.size())
	{
		auto iter = m_CommentPromptVector.end();
		printf_s("%s\n", *iter);
		m_CommentPromptVector.pop_back();
	}
}
