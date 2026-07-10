#include <Library/Console.hpp>

#include <thread>
#include <string>
#include <chrono>
#include <Windows.h>


using namespace QuoteList;


void Console::CursorGotoXY(const unsigned int& x, const unsigned int& y)
{
	COORD coord = COORD();
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


COORD Console::GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}


void Console::Sleep(float seconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000)));
}


std::wstring Console::Input(const wchar_t* prompt)
{
	std::wstring input;

	std::wcout << prompt;
	std::getline(std::wcin, input);

	return input;
}
