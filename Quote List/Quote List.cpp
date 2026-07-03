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
UI::Menu mainMenu("Quotes List");



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
	// It's impossible to create empty quote
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


static void ShowQuotesList()
{
	system("cls");

	std::cout << "Quotes list" << "\n\n";

	if (quotes.size() != 0)
	{
		for (const Quote& quote : quotes)
		{
			quote.Print();
		}
	}
	else
	{
		std::cout << "It's empty so far :(" << std::endl;
	}

	std::cout << "\nPress ESC to go back...";

	UI::Menu quotesList("", &mainMenu);
	quotesList.Open(false);
}


int main()
{
	std::setlocale(LC_ALL, "");

	// Menu Test
	mainMenu.AddOption(UI::MenuOption("Add quote", []() { CreateQuote(&quotes, &mainMenu); }));
	mainMenu.AddOption(UI::MenuOption("Quotes list", []() { ShowQuotesList(); }));
	mainMenu.AddOption(UI::MenuOption("Import quotes", []() {}));
	mainMenu.AddOption(UI::MenuOption("Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption("GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption("Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
