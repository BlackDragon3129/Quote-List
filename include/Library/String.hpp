#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


namespace QuoteList
{
	struct String
	{
		static std::vector<std::wstring> Split(const std::wstring& str, const wchar_t& delimeter)
		{
			std::wstringstream stream(str);
			std::wstring item;

			std::vector<std::wstring> elements;

			while (std::getline(stream, item, delimeter))
			{
				elements.push_back(item);
			}

			return elements;
		}
	};
}
