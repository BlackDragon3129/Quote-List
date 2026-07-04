#include <iostream>
#include <exception>
#include <clocale>
#include <vector>
#include <map>
#include <string>

#include <Quote.hpp>
#include <BaseLibrary.hpp>

#include <UI/Menu.hpp>
#include <UI/MenuOption.hpp>

using namespace std;
using namespace QuoteList;



// The list of quotes
std::vector<Quote> quotes;
std::map<std::string, std::vector<Quote*>> quotesByAuthors, quotesBySources;

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

	Quote newQuote = Quote(content, author, source);
	quotesList->push_back(newQuote);

	// Author found
	if (quotesByAuthors.find(author) != quotesByAuthors.end())
	{
		quotesByAuthors[author].push_back(&newQuote);
	}
	// Author not found
	else
	{
		quotesByAuthors.insert({ author, { &newQuote } });
	}

	// Source found
	if (quotesBySources.find(source) != quotesBySources.end())
	{
		quotesBySources[source].push_back(&newQuote);
	}
	// Source not found
	else
	{
		quotesBySources.insert({ source, { &newQuote } });
	}

	std::cout << "The quote has been successfully created!" << std::endl;
	Sleep(2.0f);

	menu->Draw();
}


static void ShowQuotesList()
{
	UI::Menu sortTypeMenu("Chooce sort type", &mainMenu);

	sortTypeMenu.AddOption(UI::MenuOption("Sort by authors", []() {}));
	sortTypeMenu.AddOption(UI::MenuOption("Sort by sources", []() {}));

	sortTypeMenu.AddOption
	(
		UI::MenuOption
		(
			"Show full list",
			[&sortTypeMenu]() 
			{
				system("cls");

				std::cout << "Full quotes list" << "\n\n";

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

				UI::Menu crutchMenu("", &sortTypeMenu);
				crutchMenu.Open(false);
			}
		)
	);
	sortTypeMenu.AddOption(UI::MenuOption("Back", [&sortTypeMenu]() { sortTypeMenu.Close(); }));

	sortTypeMenu.Open();
}


int main()
{
	std::setlocale(LC_ALL, "");

	// Menu initialisation
	mainMenu.AddOption(UI::MenuOption("Add quote", []() { CreateQuote(&quotes, &mainMenu); }));
	mainMenu.AddOption(UI::MenuOption("Quotes list", []() { ShowQuotesList(); }));
	mainMenu.AddOption(UI::MenuOption("Import quotes", []() {}));
	mainMenu.AddOption(UI::MenuOption("Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption("GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption("Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
