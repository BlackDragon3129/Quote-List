#pragma once
#include <Quote.hpp>
#include <vector>


namespace QuoteList
{
	namespace QuotesHolding
	{
		struct QuotesSaver
		{
			static void Save(const std::vector<Quote>& quotes);
		};
	}
}
