#include <QuotesHolding/Cryptographer.hpp>
#include <BaseLibrary.hpp>
#include <fstream>

using namespace QuoteList;
using namespace QuoteList::QuotesHolding;


std::wstring Cryptographer::Crypt(const std::wstring& originalData)
{
	int keys[] = { Randint(1, 15), Randint(1, 7), Randint(1, 5) };

	std::wstring cryptedData =
		std::to_wstring(keys[0]) + "," +
		std::to_wstring(keys[1]) + "," +
		std::to_wstring(keys[2]) + '\n';

	for (const wchar_t& symbol : originalData)
	{
		cryptedData.append((symbol + keys[0] - keys[1]) * keys[2]);
	}

	return cryptedData;
}


std::wstring Cryptographer::Decrypt(const std::wstring& cryptedData);
