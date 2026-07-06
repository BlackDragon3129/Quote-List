#include <QuotesHolding/QuotesSaver.hpp>
#include <BaseLibrary.hpp>

#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace QuoteList::QuotesHolding;


void QuotesSaver::Save(const std::vector<Quote>& quotes)
{
	std::wstring targetPath = GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	SHCreateDirectoryExW(NULL, targetPath.c_str(), NULL);

	std::wofstream saveFile;
	saveFile.open(targetPath + targetFile);

	if (saveFile.is_open())
	{
		for (const Quote& quote : quotes)
		{
			saveFile <<
				quote.Content << std::endl <<
				quote.Author << std::endl <<
				quote.Source << std::endl;
		}
	}

	saveFile.close();
}
