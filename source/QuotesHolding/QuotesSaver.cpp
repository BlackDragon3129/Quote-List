#include <QuotesHolding/QuotesSaver.hpp>
#include <QuotesHolding/Cryptographer.hpp>

#include <Library/LibrariesRoot.hpp>

#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <Windows.h>


using namespace QuoteList;
using namespace QuoteList::QuotesHolding;


void QuotesSaver::Save(const std::vector<Quote>& quotes)
{
	// Formating and crypting data
	std::wstring data = L"";
	for (const Quote& quote : quotes)
	{
		data.append
		(
			quote.Content + L'\n' +
			quote.Author + L'\n' +
			quote.Source + L'\n'
		);
	}
	data = Cryptographer::Crypt(data);


	// Saving the data
	std::wstring targetPath = FileSystem::GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	FileSystem::WriteFile((targetPath + targetFile).c_str(), data.c_str());
}
