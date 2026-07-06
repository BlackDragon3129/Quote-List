#pragma once
#include <iostream>


namespace QuoteList
{
	namespace QuotesHolding
	{
		struct Cryptographer
		{
			Cryptographer();

			std::wstring Crypt(const std::wstring& originalData);
			std::wstring Decrypt(const std::wstring& cryptedData)
		};
	}
}
