#include <QuotesHolding/QuotesSaver.hpp>
#include <QuotesHolding/Cryptographer.hpp>
#include <BaseLibrary.hpp>

#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <Windows.h>

using namespace QuoteList::QuotesHolding;


void QuotesSaver::Save(const std::vector<Quote>& quotes)
{
	std::wstring targetPath = GetAppDataPath() + L"BlackDragon3129\\QuotesList\\";
	std::wstring targetFile = L"Quotes.quo";

	std::wstring data = L"";
	for (const Quote& quote : quotes)
	{
		data.append
		(
			quote.Content + L'\n' +
			quote.Author + L'\n' +
			quote.Source + L'\n'
		);
	}
	data = Cryptographer::Crypt(data);


	SHCreateDirectoryExW(NULL, targetPath.c_str(), NULL);

	std::wofstream saveFile;
	saveFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	saveFile.open(targetPath + targetFile);

	if (saveFile.is_open())
	{
		saveFile << data;
	}

	saveFile.close();
}
