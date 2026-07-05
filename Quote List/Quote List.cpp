#include <iostream>
#include <exception>
#include <clocale>
#include <vector>
#include <list>
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
std::list<std::unique_ptr<Quote>> quotesList;
std::map<std::wstring, std::vector<Quote*>> quotesByAuthors, quotesBySources;

// Menu
UI::Menu mainMenu(L"Quotes List");


static std::vector<Quote*> ListToVector(const std::list<std::unique_ptr<Quote>>& list)
{
	std::vector<Quote*> destVector;
	destVector.reserve(list.size());

	for (const std::unique_ptr<Quote>& ptr : list)
	{
		if (ptr)
		{
			destVector.push_back(ptr.get());
		}
	}

	return destVector;
}


static std::wstring Input(const wchar_t* prompt)
{
	std::wstring input;

	std::wcout << prompt;
	std::getline(std::wcin, input);

	return input;
}


static void CreateQuote()
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

	quotesList.push_back(std::make_unique<Quote>(content, author, source));

	// Author found
	quotesByAuthors[author].push_back(quotesList.back().get());

	// Source found
	quotesBySources[source].push_back(quotesList.back().get());

	std::wcout << "The quote has been successfully created!" << std::endl;
	Sleep(2.0f);

	mainMenu.Draw();
}


static void OpenQuotesList(const std::wstring& menuName, UI::Menu* previousName,
	const std::vector<Quote*>& quotes)
{
	UI::Menu quotesListMenu(menuName, previousName);

	for (const Quote* quote : quotes)
	{
		quotesListMenu.AddOption(UI::MenuOption(quote->Format(), []() {}));
	}
	quotesListMenu.AddOption(UI::MenuOption(L"Back", 
		[&quotesListMenu]() {quotesListMenu.Close(); }));

	quotesListMenu.Open();
}


static void ShowQuotesList()
{
	UI::Menu sortTypeMenu(L"Chooce sort type", &mainMenu);

	sortTypeMenu.AddOption
	(
		UI::MenuOption
		(
			L"Sort by authors", 
			[&sortTypeMenu]()
			{
				UI::Menu authorChoosingMenu(L"Choose an author", &sortTypeMenu);

				for (const auto& pair : quotesByAuthors)
				{
					authorChoosingMenu.AddOption
					(
						UI::MenuOption
						(
							(pair.first == L"" ? L"Unknown author" : pair.first.c_str()),
							[&authorChoosingMenu,
							&authorName = pair.first, &authorQuotes = pair.second]()
							{
								OpenQuotesList(L"Quotes from " + authorName,
									&authorChoosingMenu, authorQuotes);
							}
						)
					);
				}

				authorChoosingMenu.AddOption(UI::MenuOption(L"Back",
					[&authorChoosingMenu]() { authorChoosingMenu.Close(); }));

				authorChoosingMenu.Open();
			}
		)
	);

	sortTypeMenu.AddOption
	(
		UI::MenuOption
		(
			L"Sort by sources",
			[&sortTypeMenu]()
			{
				UI::Menu sourceChoosingMenu(L"Choose a source", &sortTypeMenu);

				for (const auto& pair : quotesBySources)
				{
					sourceChoosingMenu.AddOption
					(
						UI::MenuOption
						(
							(pair.first == L"" ? L"Unknown source" : pair.first.c_str()),
							[&sourceChoosingMenu, 
							&sourceName = pair.first, &sourceQuotes = pair.second]()
							{
								OpenQuotesList(L"Quotes from " + sourceName,
									&sourceChoosingMenu, sourceQuotes);
							}
						)
					);
				}

				sourceChoosingMenu.AddOption(UI::MenuOption(L"Back",
					[&sourceChoosingMenu]() { sourceChoosingMenu.Close(); }));

				sourceChoosingMenu.Open();
			}
		)
	);

	sortTypeMenu.AddOption
	(
		UI::MenuOption
		(
			L"Show full list",
			[&sortTypeMenu]() 
			{
				OpenQuotesList(L"Full quotes list", &sortTypeMenu, ListToVector(quotesList));
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
	mainMenu.AddOption(UI::MenuOption(L"Add quote", []() { CreateQuote(); }));
	mainMenu.AddOption(UI::MenuOption(L"Quotes list", []() { ShowQuotesList(); }));
	mainMenu.AddOption(UI::MenuOption(L"Import quotes", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
