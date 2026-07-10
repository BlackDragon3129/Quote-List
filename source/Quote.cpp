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


std::wstring Quote::Format() const
{
	std::wstring author = (Author.empty() ? L"unknown author" : Author);
	// «Content» - (c) Author
	std::wstring formatedQuote = L"«" + Content + L"» - (c) " + author;
	// If source is not empty
	// «Content» - (c) Author, «Source»
	if (Source != L"")
		formatedQuote += L", from «" + Source + L"»";

	return formatedQuote;
}


bool Quote::operator==(const Quote& other)
{
	return
		Content == other.Content &&
		Author == other.Author &&
		Source == other.Source;
}
