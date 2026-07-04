#pragma once

#include <iostream>
#include <io.h>
#include <fcntl.h>


namespace QuoteList
{
	struct Quote
	{
		std::wstring Content, Author, Source;

		Quote(const std::wstring& content, const std::wstring& author = L"", 
			const std::wstring& source = L"");

		void Print() const;
	};
}
