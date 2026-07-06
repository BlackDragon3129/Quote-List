#pragma once

#include <Quote.hpp>
#include <vector>


namespace QuoteList
{
	namespace QuotesHolding
	{
		struct QuotesLoader
		{
			static std::vector<Quote> Load();
		};
	}
}

