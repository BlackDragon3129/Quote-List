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
#include <Library/LibrariesRoot.hpp>

#include <UI/Menu.hpp>
#include <UI/MenuOption.hpp>

#include <QuotesHolding/QuotesSaver.hpp>
#include <QuotesHolding/QuotesLoader.hpp>
#include <QuotesHolding/Cryptographer.hpp>

using namespace std;
using namespace QuoteList;
using namespace QuoteList::QuotesHolding;



// The list of quotes
std::list<std::unique_ptr<Quote>> quotesList;
std::map<std::wstring, std::vector<Quote*>> quotesByAuthors, quotesBySources;

// Menu
UI::Menu mainMenu(L"Quotes List");


static void SaveQuotes()
{
	QuotesSaver::Save(Vector::PtrVectorToValues(Vector::ListToVector(quotesList)));
}


static void AddQuote(const Quote& newQuote)
{
	quotesList.push_back(std::make_unique<Quote>(newQuote));
	quotesByAuthors[newQuote.Author].push_back(quotesList.back().get());
	quotesBySources[newQuote.Source].push_back(quotesList.back().get());
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
		mainMenu.Draw();
		return;
	}

	author = Input(L"Enter quote's author (if the author is unknown, leave the field empty): ");
	source = Input(L"Enter quote's source (if the source is unknown, leave the field empty): ");

	AddQuote(Quote(content, author, source));

	SaveQuotes();

	std::wcout << "The quote has been successfully created!" << std::endl;
	Sleep(2.0f);

	mainMenu.Draw();
}


static void DeleteQuote(Quote* quote)
{
	// Deletion from quotesByAuthors
	auto authorPair = quotesByAuthors.find(quote->Author);
	auto& authorQuotes = authorPair->second;
	authorQuotes.erase
	(
		std::find
		(
			authorQuotes.begin(),
			authorQuotes.end(),
			quote
		)
	);
	if (authorQuotes.empty())
	{
		quotesByAuthors.erase(authorPair);
	}

	// Deletion from quotesBySources
	auto sourcePair = quotesBySources.find(quote->Source);
	auto& sourceQuotes = sourcePair->second;
	sourceQuotes.erase
	(
		std::find
		(
			sourceQuotes.begin(),
			sourceQuotes.end(),
			quote
		)
	);
	if (sourceQuotes.empty())
	{
		quotesBySources.erase(sourcePair);
	}

	// Deletion from the main list
	quotesList.remove_if
	(
		[quote](const std::unique_ptr<Quote>& ptr)
		{
			return ptr.get() == quote;
		}
	);
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
				[&previousMenu, &quotesListMenu, &quote]()
				{
					UI::Menu optionMenu(L"What to do with the quote?", &quotesListMenu);

					optionMenu.AddOption
					(
						UI::MenuOption
						(
							L"Edit",
							[&previousMenu, &quotesListMenu, &optionMenu, &quote]()
							{
								UI::Menu whatToEditMenu(L"What do you want to edit?", &optionMenu);
								
								whatToEditMenu.AddOption
								(
									UI::MenuOption
									(
										L"Content", 
										[&previousMenu, &quotesListMenu, &optionMenu, &whatToEditMenu, &quote]()
										{
											system("cls");

											std::wstring newContent = Input(L"Enter new quote's content: ");
											if (newContent.empty())
											{
												std::wcout << L"The quote can not be empty!";

												Sleep(2.0f);

												whatToEditMenu.Draw();
											}
											else
											{
												quote->Content = newContent;
												std::wcout << L"The content of the quote has been " <<
													"successfully changed!" << std::endl;

												std::wcout << "Saving the change..." << std::endl;
												SaveQuotes();
												std::wcout << "The change has been saved!";

												Sleep(2.0f);

												whatToEditMenu.Close(false);
												optionMenu.Close(false);
												quotesListMenu.Close(false);
												previousMenu->Close(true);
											}
										}
									)
								);
								whatToEditMenu.AddOption
								(
									UI::MenuOption
									(
										L"Author", 
										[&previousMenu, &quotesListMenu, &optionMenu, &whatToEditMenu, &quote]()
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

											std::wcout << L"Author has been successfully changed!" << std::endl;

											std::wcout << "Saving the change..." << std::endl;
											SaveQuotes();
											std::wcout << "The change has been saved!";

											Sleep(2.0f);
											
											whatToEditMenu.Close(false);
											optionMenu.Close(false);
											quotesListMenu.Close(false);
											previousMenu->Close(true);
										}
									)
								);
								whatToEditMenu.AddOption
								(
									UI::MenuOption
									(
										L"Source",
										[&previousMenu, &quotesListMenu, &optionMenu, &whatToEditMenu, &quote]()
										{
											system("cls");

											std::wstring newSource = Input(L"Enter new quote's source: ");

											std::vector<Quote*>* sourceQuotes = &quotesBySources[quote->Source];
											sourceQuotes->erase
											(
												std::find(sourceQuotes->begin(), sourceQuotes->end(), quote)
											);
											if (sourceQuotes->size() == 0)
											{
												quotesBySources.erase(quote->Source);
											}

											quote->Source = newSource;
											quotesBySources[newSource].push_back(quote);

											std::wcout << L"Source has been successfully changed!";

											std::wcout << "Saving the change..." << std::endl;
											SaveQuotes();
											std::wcout << "The change has been saved!";

											Sleep(2.0f);

											whatToEditMenu.Close(false);
											optionMenu.Close(false);
											quotesListMenu.Close(false);
											previousMenu->Close(true);
										}
									)
								);
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
							[&previousMenu, &quotesListMenu, &optionMenu, &quote]()
							{
								UI::Menu areYouSureMenu(L"Are you sure to delete the quote «" +
									quote->Content + L"»", &optionMenu);

								areYouSureMenu.AddOption
								(
									UI::MenuOption
									(
										L"Yes",
										[&previousMenu, &quotesListMenu, &optionMenu, &areYouSureMenu, &quote]()
										{
											system("cls");

											DeleteQuote(quote);

											std::wcout << "The quote has been successfully deleted!";

											std::wcout << "Saving the change..." << std::endl;
											SaveQuotes();
											std::wcout << "The change has been saved!";

											Sleep(2.0f);

											areYouSureMenu.Close(false);
											optionMenu.Close(false);
											quotesListMenu.Close(false);
											previousMenu->Close(true);
										}
									)
								);
								areYouSureMenu.AddOption(UI::MenuOption(L"No",
									[&areYouSureMenu]() { areYouSureMenu.Close(); }));

								areYouSureMenu.Open();
							}
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
				OpenQuotesList(L"Full quotes list", &sortTypeMenu, Vector::ListToVector(quotesList));
			}
		)
	);
	sortTypeMenu.AddOption(UI::MenuOption(L"Back", [&sortTypeMenu]() { sortTypeMenu.Close(); }));

	sortTypeMenu.Open();
}


int wmain(int argc, wchar_t* argv[])
{
	srand(time(NULL));

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);


	// Quotes loading
	std::vector<Quote> quotes = QuotesLoader::Load();

	for (const Quote quote : quotes)
	{
		AddQuote(quote);
	}


	// Menu initialisation
	mainMenu.AddOption(UI::MenuOption(L"Add quote", []() { CreateQuote(); }));
	mainMenu.AddOption(UI::MenuOption(L"Quotes list", []() { ShowQuotesList(); }));
	// TODO: add options
	// mainMenu.AddOption(UI::MenuOption(L"Import quotes", []() {}));
	// mainMenu.AddOption(UI::MenuOption(L"Settings", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"GitHub", []() {}));
	mainMenu.AddOption(UI::MenuOption(L"Exit", []() { exit(0); }));

	mainMenu.Open();

	return 0;
}
