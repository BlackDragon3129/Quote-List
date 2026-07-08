#pragma once

#include <iostream>
#include <vector>


namespace QuoteList
{
	struct String
	{
		static std::vector<std::wstring> Split(const std::wstring& str, const wchar_t& delimeter);
	};
}
