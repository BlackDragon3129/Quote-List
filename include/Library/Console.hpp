#pragma once

#include <iostream>


namespace QuoteList
{
	struct Console
	{
		static void CursorGotoXY(const unsigned int& x, const unsigned int& y);
		static void Sleep(float seconds);
		static std::wstring Input(const wchar_t* prompt = L"");
	};
}
