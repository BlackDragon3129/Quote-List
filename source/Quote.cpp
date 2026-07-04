#include <Quote.hpp>
#include <iostream>
#include <exception>
#include <format>
#include <io.h>
#include <fcntl.h>

using namespace QuoteList;

Quote::Quote(const std::wstring& content, const std::wstring& author, const std::wstring& source)
{
	if (content == L"")
		throw std::invalid_argument("The quote can not be empty");

	Content = content;
	Author = author;
	Source = source;
}


void Quote::Print() const
{
	std::wstring author = (Author == L"" ? L"unknown author" : Author);
	// «Content» - (c) Author
	std::wstring out = L"«" + Content + L"»" + L" - " + author;
	// If source is not empty
	// «Content» - (c) Author, «Source»
	if (Source != L"")
		out += L", «" + Source + L"»";

	std::wcout << out << std::endl;
}
