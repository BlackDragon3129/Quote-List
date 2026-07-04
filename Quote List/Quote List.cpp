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
std::list<std::unique_ptr<Quote>> quotes;
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
								system("cls");

								std::wcout << L"Quotes from " << authorName << L"\n\n";

								// Print every quote from the chosen author
								for (const Quote* quote : authorQuotes)
								{
									std::wcout << quote->Format() << std::endl;
								}

								std::wcout << L"\nPress ESC to go back...";

								// For going back by Esc
								UI::Menu crutchMenu(L"", &authorChoosingMenu);
								crutchMenu.Open(false);
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
								system("cls");

								std::wcout << L"Quotes from " << sourceName << L"\n\n";

								// Print every quote from the chosen source
								for (const Quote* quote : sourceQuotes)
								{
									std::wcout << quote->Format() << std::endl;
								}

								std::wcout << L"\nPress ESC to go back...";

								// For going back by Esc
								UI::Menu crutchMenu(L"", &sourceChoosingMenu);
								crutchMenu.Open(false);
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
				system("cls");

				// Header
				std::wcout << L"Full quotes list" << "\n\n";

				// If there are any quotes
				if (quotes.size() != 0)
				{
					// Print every quote
					for (const unique_ptr<Quote>& quote : quotes)
					{
						std::wcout << quote.get()->Format() << std::endl;
					}
				}
				// If there are no quotes
				else
				{
					std::wcout << L"It's empty so far :(" << std::endl;
				}

				std::wcout << L"\nPress ESC to go back...";

				// For going back by Esc
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
	mainMenu.AddOption(UI::MenuOption(L"Add quote", []() { CreateQuote(); }));
	mainMenu.AddOption(UI::MenuOption(L"Delete quote", []() { DeleteQuote(); }));
	mainMenu.AddOption(UI::MenuOption(L"Quotes list", []() { ShowQuotesList(); }));
	mainMenu.AddOption(UI::MenuOption(L"Import quotes", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
