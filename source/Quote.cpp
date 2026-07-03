#include <Quote.hpp>
#include <iostream>
#include <exception>

using namespace QuoteList;

Quote::Quote(const std::string& content, const std::string& author, const std::string& source)
{
	if (content == "")
		throw std::invalid_argument("The quote can not be empty");

	Content = content;
	Author = "";
	Source = "";
}


void Quote::Print() const
{
	std::cout << "«" << Content << "» - (c) " << Author << ", «" << Source << "»" << std::endl;
}
