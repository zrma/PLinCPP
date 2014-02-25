#pragma once
#include <string>
#include <windows.h>

enum ColorSet
{
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY_BLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKY_BLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE
};

class COutputUI
{
public:
	COutputUI(void);
	~COutputUI(void);

	void		Clear();
	void		Clear(int line);
	void		SetColor(ColorSet backColor, ColorSet fontColor);

	void		CursorToPosition(int x, int y);
	void		CursorToPosition(COORD CursorPosition);

	void		BroadCast(char* message, bool newLine = true);

private:
	SMALL_RECT	GetSizeOfWindows();

private:
	HANDLE		m_HandleStdOutput;
	COORD			m_Origin;
	CONSOLE_SCREEN_BUFFER_INFO
						m_ScreenInfo;
};