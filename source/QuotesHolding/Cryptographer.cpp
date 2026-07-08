#include <QuotesHolding/Cryptographer.hpp>
#include <Library/LibrariesRoot.hpp>
#include <fstream>

using namespace QuoteList;
using namespace QuoteList::QuotesHolding;


std::wstring Cryptographer::Crypt(const std::wstring& originalData)
{
	wchar_t keys[] = { Random::Randint(1, 15), Random::Randint(1, 7), Random::Randint(1, 5) };

	std::wstring cryptedData =
		std::to_wstring(keys[0]) + L"," +
		std::to_wstring(keys[1]) + L"," +
		std::to_wstring(keys[2]) + L'\n';

	for (const wchar_t& symbol : originalData)
	{
		cryptedData.push_back((symbol + keys[0] - keys[1]) * keys[2]);
	}

	return cryptedData;
}


std::wstring Cryptographer::Decrypt(const std::wstring& cryptedData)
{
	std::vector<std::wstring> keysAndData = String::Split(cryptedData, '\n');

	// Keys go before data
	std::vector<std::wstring> keysString = String::Split(keysAndData[0], L',');
	int keys[] =
	{
		std::stoi(keysString[0]),
		std::stoi(keysString[1]),
		std::stoi(keysString[2])
	};

	std::wstring decryptedData = L"";

	for (const wchar_t& symbol : keysAndData[1])
	{
		decryptedData.push_back(symbol / keys[2] + keys[1] - keys[0]);
	}

	return decryptedData;
}
