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
#include <algorithm>

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
		std::wcout << L"Quote must be not empty!" << std::endl;
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


static void OpenQuotesList(const std::wstring& menuName, UI::Menu* previousMenu,
	std::vector<Quote*> quotes)
{
	UI::Menu quotesListMenu(menuName, previousMenu);

	for (Quote* quote : quotes)
	{
		quotesListMenu.AddOption
		(
			UI::MenuOption
			(
				quote->Format(),
				[&quotesListMenu, &quote]()
				{
					UI::Menu optionMenu(L"What to do with the quote?", &quotesListMenu);

					optionMenu.AddOption
					(
						UI::MenuOption
						(
							L"Edit",
							[&optionMenu, &quote]()
							{
								UI::Menu whatToEditMenu(L"What do you want to edit?", &optionMenu);
								
								whatToEditMenu.AddOption
								(
									UI::MenuOption
									(
										L"Content", 
										[&whatToEditMenu, &quote]()
										{
											system("cls");

											std::wstring newContent = Input(L"Enter new quote's content: ");
											if (newContent.empty())
											{
												std::wcout << L"The quote can not be empty!";
											}
											else
											{
												quote->Content = newContent;
												std::wcout << L"The content of the quote has been " <<
													"successfully changed!";
											}

											Sleep(2.0f);

											whatToEditMenu.Draw();
										}
									)
								);
								whatToEditMenu.AddOption
								(
									UI::MenuOption
									(
										L"Author", 
										[&whatToEditMenu, &quote]()
										{
											system("cls");

											std::wstring newAuthor = Input(L"Enter new quote's author: ");

											std::vector<Quote*>* authorQuotes = &quotesByAuthors[quote->Author];
											authorQuotes->erase
											(
												std::find(authorQuotes->begin(), authorQuotes->end(), quote)
											);
											if (authorQuotes->size() == 0)
											{
												quotesByAuthors.erase(quote->Author);
											}

											quote->Author = newAuthor;
											quotesByAuthors[newAuthor].push_back(quote);

											std::wcout << L"Author has been successfully changed!";

											Sleep(2.0f);
											whatToEditMenu.Draw();
										}
									)
								);
								whatToEditMenu.AddOption(UI::MenuOption(L"Source", []() {}));
								whatToEditMenu.AddOption(UI::MenuOption(L"Back",
									[&whatToEditMenu]() { whatToEditMenu.Close(); }));

								whatToEditMenu.Open();
							}
						)
					);
					optionMenu.AddOption
					(
						UI::MenuOption
						(
							L"Delete",
							[]() {}
						)
					);
					optionMenu.AddOption(UI::MenuOption(L"Back",
						[&optionMenu]() {optionMenu.Close(); }));

					optionMenu.Open();
				}
			)
		);
	}
	quotesListMenu.AddOption(UI::MenuOption(L"Back", 
		[&quotesListMenu]() {quotesListMenu.Close(); }));

	quotesListMenu.Open();
}


static void OpenSortedQuotesList(const std::wstring& menuName, const std::wstring& unkownOptionName,
	UI::Menu* previousMenu, std::map<std::wstring, std::vector<Quote*>>& sortingMap)
{
	UI::Menu sortWayMenu(menuName, previousMenu);

	for (const auto& pair : sortingMap)
	{
		sortWayMenu.AddOption
		(
			UI::MenuOption
			(
				(pair.first == L"" ? unkownOptionName : pair.first),
				[&sortWayMenu, &sortWayName = pair.first, &quotes = pair.second]()
				{
					OpenQuotesList(L"Quotes from " + sortWayName, &sortWayMenu, quotes);
				}
			)
		);
	}
	sortWayMenu.AddOption(UI::MenuOption(L"Back", [&sortWayMenu]() {sortWayMenu.Close(); }));

	sortWayMenu.Open();
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
				OpenSortedQuotesList(L"Choose an author", L"Unknown author", &sortTypeMenu,
					quotesByAuthors);
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
				OpenSortedQuotesList(L"Choose a source", L"Unknown source", &sortTypeMenu,
					quotesBySources);
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
