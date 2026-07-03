#pragma once
#include <Windows.h>
#include <iostream>
#include <functional>

namespace QuoteList
{
	static void CursorGotoXY(const unsigned int& x, const unsigned int& y)
	{
		COORD coord = COORD();
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	typedef std::function<void()> Function;
}
