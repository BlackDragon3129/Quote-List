#pragma once
#include <Windows.h>
#include <shlobj.h>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>


namespace QuoteList
{
	


	static int Randint(const int& min, const int& max)
	{
		return min + rand() % (max - min);
	}


	static std::vector<std::wstring> Split(const std::wstring& str, const wchar_t& delimeter)
	{
		std::wstringstream stream(str);
		std::wstring item;

		std::vector<std::wstring> elements;

		while (std::getline(stream, item, delimeter))
		{
			elements.push_back(item);
		}

		return elements;
	}


	static void CursorGotoXY(const unsigned int& x, const unsigned int& y)
	{
		COORD coord = COORD();
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}


	static void Sleep(float seconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000)));
	}


	static std::wstring Input(const wchar_t* prompt)
	{
		std::wstring input;

		std::wcout << prompt;
		std::getline(std::wcin, input);

		return input;
	}


	static std::wstring GetAppDataPath()
	{
		PWSTR pszPath = NULL;
		GUID folderId = FOLDERID_LocalAppData;

		HRESULT hr = SHGetKnownFolderPath(folderId, 0, NULL, &pszPath);

		if (SUCCEEDED(hr))
		{
			std::wstring path(pszPath);
			CoTaskMemFree(pszPath);
			return path + L"\\";
		}

		return L"";
	}


	typedef std::function<void()> Function;
}
