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



// The list of quotes
std::vector<Quote> quotes;
// Menu
UI::Menu menu("Quotes List");



static std::string Input(const char* prompt)
{
	std::string input;

	std::cout << prompt;
	std::getline(std::cin, input);

	return input;
}


static void CreateQuote(std::vector<Quote>* quotesList, UI::Menu* menu)
{
	system("cls");

	std::string content, author, source;

	content = Input("Enter quote's content: ");
	if (content == "")
	{
		std::cout << "Quote must be not empty!" << std::endl;
		Sleep(2.0f);
		return;
	}

	author = Input("Enter quote's author (if the author is unknown, leave the field empty): ");
	source = Input("Enter quote's source (if the source is unknown, leave the field empty): ");

	quotesList->push_back(Quote(content, author, source));

	std::cout << "The quote has been successfully created!" << std::endl;
	Sleep(2.0f);

	menu->Draw();
}


int main()
{
	std::setlocale(LC_ALL, "");

	// Menu Test
	menu.AddOption(UI::MenuOption("Add quote", []() { CreateQuote(&quotes, &menu); }));
	menu.AddOption(UI::MenuOption("Quotes list", []() {}));
	menu.AddOption(UI::MenuOption("Import quotes", []() {}));
	menu.AddOption(UI::MenuOption("Settings", []() {}));
	menu.AddOption(UI::MenuOption("GitHub", []() {}));
	menu.AddOption(UI::MenuOption("Exit", []() { exit(0); }));

	menu.Open();

	return 0;
}
