#include <QuotesHolding/QuotesLoader.hpp>
#include <QuotesHolding/Cryptographer.hpp>
#include <Quote.hpp>

#include <Library/LibrariesRoot.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <string> 
#include <locale>
#include <codecvt>

using namespace QuoteList;
using namespace QuoteList::QuotesHolding;


std::vector<Quote> QuotesLoader::Load()
{
	// Reading data from the save file
	std::wstring targetPath = FileSystem::GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	std::wstring data = FileSystem::ReadFile((targetPath + targetFile).c_str());
	if (data.empty())
	{
		return std::vector<Quote>();
	}

	system("cls");
	std::wcout << data;
	Console::Sleep(3.0f);


	// Decrypting and loading
	std::vector<std::wstring> lines = String::Split(Cryptographer::Decrypt(data), L'\n');

	std::vector<Quote> quotes;
	std::size_t quotesCount = lines.size() / 3;
	quotes.reserve(quotesCount);

	for (int quote = 0; quote < quotesCount; quote++)
	{
		quotes.push_back
		(
			Quote
			(
				lines[quote * 3],
				lines[quote * 3 + 1],
				lines[quote * 3 + 2]
			)
		);
	}

	return quotes;
}
