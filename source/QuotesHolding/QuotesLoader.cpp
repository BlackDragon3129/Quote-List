#include <QuotesHolding/QuotesLoader.hpp>
#include <QuotesHolding/Cryptographer.hpp>
#include <BaseLibrary.hpp>
#include <Quote.hpp>
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
	std::wstring targetPath = GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	std::wifstream saveFile(targetPath + targetFile);
	saveFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::wstring data = L"";

	std::wstring line;
	if (saveFile.is_open())
	{
		while (std::getline(saveFile, line))
		{
			data.append(line + L'\n');
		}
	}
	else
	{
		return std::vector<Quote>();
	}

	saveFile.close();

	std::vector<std::wstring> lines = Split(Cryptographer::Decrypt(data), L'\n');

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
