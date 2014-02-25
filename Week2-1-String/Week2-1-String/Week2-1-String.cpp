// Week2-1-String.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	char szDebug[32] = { 0, };
	printf_s("초기화 없이 출력 : %s\n", szDebug);

	char 한글변수[32] = "한글 변수명 성공";
	printf_s("한글 변수명 : %s\n", 한글변수);

	char szText[] = "I Love You";
	printf_s("szText[] 원본 : %s\n", szText);

	// 1. 문자열 변경 = 에러
	// szText = "I Hate You";
	char szText2[] = "I Hate You";
	sprintf_s(szText, "%s", szText2);
	printf_s("sprintf_s 변경 : %s\n", szText);

	// 2. 문자열 복사
	strcpy_s(szText, szText2);
	printf_s("strcpy_s 복사 : %s\n", szText);

	// 3. 문자열 추가 - 안됨
	// sprintf_s(szText, "%s - 문자열 추가", szText);
	char szNewText[32] = { 0, };
	sprintf_s(szNewText, "%s - 문자열 추가", szText);
	printf_s("sprintf_s 복사 : %s\n", szNewText);

	printf_s("------------------------------\n");

	std::string strText = "I Love String";
	printf_s("std::string 원본 : %s\n", strText.c_str());

	// 1. 문자열 변경
	strText = "I Hate String";
	printf_s("= 대입 변경 : %s\n", strText.c_str());

	// 2. 문자열 복사 - 에러
	// szText = szText1;
	std::string strText2 = "I Hate You";
	strText = strText2;
	printf_s("= 대입 복사 : %s\n", strText.c_str());

	// 3. 문자열 추가
	strText2 = "I Hate You";
	strText2 += " - 문자열 추가";
	printf_s("+= 대입 복사 : %s\n", strText2.c_str());

	getchar();

	return 0;
}

