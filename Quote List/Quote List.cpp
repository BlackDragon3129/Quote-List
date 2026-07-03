#include <iostream>
#include <exception>
#include <clocale>
#include <vector>
#include <string>

#include <Quote.hpp>
#include <BaseLibrary.hpp>

#include <UI/Menu.hpp>
#include <UI/MenuOption.hpp>

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

	// Menu Test
	UI::Menu menu("Quotes List");

	menu.AddOption(UI::MenuOption("Add quote", []() {} ));
	menu.AddOption(UI::MenuOption("Quotes list", []() {}));
	menu.AddOption(UI::MenuOption("Import quotes", []() {}));
	menu.AddOption(UI::MenuOption("Settings", []() {}));
	menu.AddOption(UI::MenuOption("GitHub", []() {}));
	menu.AddOption(UI::MenuOption("Add quote", []() { exit(0); }));

	menu.Draw();

	// Input loop
	while (true)
	{

	}

	return 0;
}
