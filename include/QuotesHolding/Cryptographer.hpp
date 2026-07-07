#pragma once
#include <iostream>


namespace QuoteList
{
	namespace QuotesHolding
	{
		struct Cryptographer
		{
			static std::wstring Crypt(const std::wstring& originalData);
			static std::wstring Decrypt(const std::wstring& cryptedData);
		};
	}
}
