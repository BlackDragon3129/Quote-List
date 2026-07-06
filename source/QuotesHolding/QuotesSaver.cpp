#include <QuotesHolding/QuotesSaver.hpp>
#include <BaseLibrary.hpp>

#include <iostream>
#include <fstream>

using namespace QuoteList::QuotesHolding;


void QuotesSaver::Save(const std::vector<Quote>& quotes)
{
	std::wstring targetPath = GetAppDataPath() + L"BlackDragon3129\\QuotesList\\Quotes.quo";

	std::ofstream saveFile;
	saveFile.open(targetPath);

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
