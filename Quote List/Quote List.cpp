#include <iostream>
#include <exception>
#include <clocale>
#include <vector>
#include <string>

#include <Quote.hpp>

using namespace std;
using namespace QuoteList;


static std::string Input(const char* prompt)
{
	std::string input;

	std::cout << prompt;
	std::getline(std::cin, input);

	return input;
}


int main()
{
	std::setlocale(LC_ALL, "");

	// The list of every quote
	std::vector<Quote> quotes;

	// Quote creation
	std::string content, author, source;

	content = Input("Enter quote's content: ");
	author = Input("Enter quote's author (if the author is unknown, type \"-\"): ");
	source = Input("Enter quote's source (book/film/song where the quote has been taken; if it's unknown, type \"-\"): ");

	author = author == "-" ? "" : author;
	source = source == "-" ? "" : source;

	try
	{
		Quote(content, author, source).Print();
	}
	catch (std::invalid_argument)
	{
		std::cout << "Content must be not an empty string!" << std::endl;
	}

	return 0;
}
