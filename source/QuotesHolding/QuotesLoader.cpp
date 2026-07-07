#include <QuotesHolding/QuotesLoader.hpp>
#include <BaseLibrary.hpp>
#include <Quote.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string> 

using namespace QuoteList;
using namespace QuoteList::QuotesHolding;


std::vector<Quote> QuotesLoader::Load()
{
	std::wstring targetPath = GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	std::wifstream saveFile(targetPath + targetFile);
	std::vector<std::wstring> lines;

	std::wstring line = L"";
	if (saveFile.is_open())
	{
		while (std::getline(saveFile, line))
		{
			lines.push_back(line);
			line = L"";
		}
	}

	saveFile.close();

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
