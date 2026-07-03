#include <Quote.hpp>
#include <iostream>
#include <exception>
#include <format>

using namespace QuoteList;

Quote::Quote(const std::string& content, const std::string& author, const std::string& source)
{
	if (content == "")
		throw std::invalid_argument("The quote can not be empty");

	Content = content;
	Author = author;
	Source = source;
}


void Quote::Print() const
{
	std::string author = (Author == "" ? "unknown author" : Author);
	// "Content" - (c) Author
	std::string out = "\"" + Content + "\"" + " - " + author;
	// If source is not empty
	// "Content" - (c) Author, "Source"
	if (Source != "")
		out += ", \"" + Source + "\"";

	std::cout << out << std::endl;
}
