#pragma once
#include <functional>

namespace QuoteList
{
	static void CursorGotoXY(const unsigned int& x, const unsigned int& y);

	typedef std::function<void()> Function;
}
