#include "stdafx.h"
#include "OutputUI.h"

COutputUI::COutputUI(void)
{
	m_HandleStdOutput	= GetStdHandle(STD_OUTPUT_HANDLE);
	m_Origin.X = 0;
	m_Origin.Y = 0;

	COORD		newSize;

	newSize.X = 53;
	newSize.Y = 42;
	SetConsoleScreenBufferSize(m_HandleStdOutput, newSize);

	SMALL_RECT	newRect;

	newRect.Left = 0;
	newRect.Right = newSize.X-1;
	newRect.Top = 0;
	newRect.Bottom = newSize.Y-1;

	SetConsoleWindowInfo(m_HandleStdOutput, TRUE, &newRect);

	CONSOLE_CURSOR_INFO		cci;
	cci.dwSize		= 1;
	cci.bVisible	= FALSE;

	SetConsoleCursorInfo(m_HandleStdOutput, &cci);
	GetConsoleScreenBufferInfo(m_HandleStdOutput, &m_ScreenInfo);
}

COutputUI::~COutputUI(void)
{
	CloseHandle(m_HandleStdOutput);
}

// 화면 전체 지우기
void COutputUI::Clear()
{
	DWORD						length;

	FillConsoleOutputAttribute(m_HandleStdOutput, 0, m_ScreenInfo.dwMaximumWindowSize.X * m_ScreenInfo.dwMaximumWindowSize.Y,
		m_Origin, &length);
	FillConsoleOutputCharacter(m_HandleStdOutput, ' ', m_ScreenInfo.dwMaximumWindowSize.X * m_ScreenInfo.dwMaximumWindowSize.Y,
		m_Origin, &length);

	CursorToPosition(m_Origin);
}

// 화면 한 줄 지우기
void COutputUI::Clear(int line)
{
	DWORD					length;
	COORD						origin;

	origin.X = m_Origin.X;
	origin.Y = line;

	FillConsoleOutputCharacter(m_HandleStdOutput, ' ', m_ScreenInfo.dwMaximumWindowSize.X,
		origin, &length);
}

void COutputUI::SetColor( ColorSet backColor, ColorSet fontColor )
{
	SetConsoleTextAttribute(m_HandleStdOutput, (backColor << 4) | fontColor);
}

void COutputUI::CursorToPosition(int x, int y)
{
	// 방어코드
	if(x < 0 || x > m_ScreenInfo.dwSize.X || y < 0 || y > m_ScreenInfo.dwSize.Y)
		return;

	COORD CursorPosition = { (short) x, (short) y };
	CursorToPosition(CursorPosition);
}

void COutputUI::CursorToPosition( COORD CursorPosition )
{
	SetConsoleCursorPosition ( m_HandleStdOutput, CursorPosition);
}

void COutputUI::BroadCast( char* message, bool newLine)
{
	if(newLine)
		printf_s("%s \n", message);
	else
		printf_s(message);
}

SMALL_RECT COutputUI::GetSizeOfWindows()
{
	SMALL_RECT	rect = {0, };

	rect.Top = 0;
	rect.Left = 0;
	rect.Right = m_ScreenInfo.dwMaximumWindowSize.X - 1;
	rect.Bottom = m_ScreenInfo.dwMaximumWindowSize.Y - 1;

	return rect;
}