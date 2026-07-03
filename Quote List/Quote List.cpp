#include <iostream>
#include <exception>
#include <clocale>

#include <Quote.hpp>

using namespace std;
using namespace QuoteList;

int main()
{
	std::setlocale(LC_ALL, "");

	try
	{
		Quote wrongQuote("");
	}
	catch (std::invalid_argument)
	{
		std::cout << "Caught invalid_argument in the wrong quote" << std::endl;
	}

	Quote unknownQuote("Just a test quote");
	Quote myQuote("Just a test quote №2", "Me");
	Quote cppQuote("Just a test quote №3", "", "Quote list");

	unknownQuote.Print();
	myQuote.Print();
	cppQuote.Print();

	return 0;
}
