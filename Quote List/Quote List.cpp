#include <iostream>
#include <exception>
#include <clocale>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include <Quote.hpp>
#include <BaseLibrary.hpp>

#include <UI/Menu.hpp>
#include <UI/MenuOption.hpp>

using namespace std;
using namespace QuoteList;



// The list of quotes
std::vector<Quote> quotes;
std::map<std::wstring, std::vector<Quote*>> quotesByAuthors, quotesBySources;

// Menu
UI::Menu mainMenu(L"Quotes List");



static std::wstring Input(const wchar_t* prompt)
{
	std::wstring input;

	std::wcout << prompt;
	std::getline(std::wcin, input);

	return input;
}


static void CreateQuote(std::vector<Quote>* quotesList, UI::Menu* menu)
{
	system("cls");

	std::wstring content, author, source;

	content = Input(L"Enter quote's content: ");
	// It's impossible to create empty quote
	if (content == L"")
	{
		std::cout << "Quote must be not empty!" << std::endl;
		Sleep(2.0f);
		return;
	}

	author = Input(L"Enter quote's author (if the author is unknown, leave the field empty): ");
	source = Input(L"Enter quote's source (if the source is unknown, leave the field empty): ");

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

	std::wcout << "The quote has been successfully created!" << std::endl;
	Sleep(2.0f);

	menu->Draw();
}


static void ShowQuotesList()
{
	UI::Menu sortTypeMenu(L"Chooce sort type", &mainMenu);

	sortTypeMenu.AddOption(UI::MenuOption(L"Sort by authors", []() {}));
	sortTypeMenu.AddOption(UI::MenuOption(L"Sort by sources", []() {}));

	sortTypeMenu.AddOption
	(
		UI::MenuOption
		(
			L"Show full list",
			[&sortTypeMenu]() 
			{
				system("cls");

				std::wcout << L"Full quotes list" << "\n\n";

				if (quotes.size() != 0)
				{
					for (const Quote& quote : quotes)
					{
						quote.Print();
					}
				}
				else
				{
					std::wcout << L"It's empty so far :(" << std::endl;
				}

				std::wcout << L"\nPress ESC to go back...";

				UI::Menu crutchMenu(L"", &sortTypeMenu);
				crutchMenu.Open(false);
			}
		)
	);
	sortTypeMenu.AddOption(UI::MenuOption(L"Back", [&sortTypeMenu]() { sortTypeMenu.Close(); }));

	sortTypeMenu.Open();
}


int wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	// Menu initialisation
	mainMenu.AddOption(UI::MenuOption(L"Add quote", []() { CreateQuote(&quotes, &mainMenu); }));
	mainMenu.AddOption(UI::MenuOption(L"Quotes list", []() { ShowQuotesList(); }));
	mainMenu.AddOption(UI::MenuOption(L"Import quotes", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
