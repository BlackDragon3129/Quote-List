#pragma once

#include <Quote.hpp>
#include <vector>


namespace QuoteList
{
	namespace QuotesHolding
	{
		struct QuotesLoader
		{
			static std::vector<Quote> Load(const std::wstring& path = 
				FileSystem::GetAppDataPath() + L"BlackDragon3129\\QuotesList\\Quotes.quo");
		};
	}
}

