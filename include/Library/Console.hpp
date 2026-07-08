#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <Windows.h>


namespace QuoteList
{
	static void CursorGotoXY(const unsigned int& x, const unsigned int& y)
	{
		COORD coord = COORD();
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}


	static void Sleep(float seconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000)));
	}


	static std::wstring Input(const wchar_t* prompt)
	{
		std::wstring input;

		std::wcout << prompt;
		std::getline(std::wcin, input);

		return input;
	}
}
