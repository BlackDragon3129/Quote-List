#include <Quote.hpp>
#include <iostream>

using namespace QuoteList;

Quote::Quote()
{
	Author = "";
	Author = "";
}
Quote::Quote(const std::string& author)
{
	Author = author;
	Source = "";
}
Quote::Quote(const std::string& author, const std::string& source)
{
	Author = author;
	Source = source;
}
