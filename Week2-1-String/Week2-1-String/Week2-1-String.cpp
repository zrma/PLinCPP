// Week2-1-String.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	char szDebug[32] = { 0, };
	printf_s("�ʱ�ȭ ���� ��� : %s\n", szDebug);

	char �ѱۺ���[32] = "�ѱ� ������ ����";
	printf_s("�ѱ� ������ : %s\n", �ѱۺ���);

	char szText[] = "I Love You";
	printf_s("szText[] ���� : %s\n", szText);

	// 1. ���ڿ� ���� = ����
	// szText = "I Hate You";
	char szText2[] = "I Hate You";
	sprintf_s(szText, "%s", szText2);
	printf_s("sprintf_s ���� : %s\n", szText);

	// 2. ���ڿ� ����
	strcpy_s(szText, szText2);
	printf_s("strcpy_s ���� : %s\n", szText);

	// 3. ���ڿ� �߰� - �ȵ�
	// sprintf_s(szText, "%s - ���ڿ� �߰�", szText);
	char szNewText[32] = { 0, };
	sprintf_s(szNewText, "%s - ���ڿ� �߰�", szText);
	printf_s("sprintf_s ���� : %s\n", szNewText);

	printf_s("------------------------------\n");

	std::string strText = "I Love String";
	printf_s("std::string ���� : %s\n", strText.c_str());

	// 1. ���ڿ� ����
	strText = "I Hate String";
	printf_s("= ���� ���� : %s\n", strText.c_str());

	// 2. ���ڿ� ���� - ����
	// szText = szText1;
	std::string strText2 = "I Hate You";
	strText = strText2;
	printf_s("= ���� ���� : %s\n", strText.c_str());

	// 3. ���ڿ� �߰�
	strText2 = "I Hate You";
	strText2 += " - ���ڿ� �߰�";
	printf_s("+= ���� ���� : %s\n", strText2.c_str());

	getchar();

	return 0;
}

