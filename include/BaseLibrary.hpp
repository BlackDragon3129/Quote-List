#pragma once
#include <Quote.hpp>
#include <list>
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
	struct Math
	{
		template<typename T>
		static T Clamp(const T& val, const T& min, const T& max)
		{
			static_assert(std::is_arithmetic_v<T>, "Math::Clamp T must be a number type");

			if (val < min)
				return min;
			else if (val > max)
				return max;
			return val;
		}

		template<typename T>
		static T ClampReverse(const T& val, const T& min, const T& max)
		{
			static_assert(std::is_arithmetic_v<T>, "Math::Clamp T must be a number type");

			if (val < min)
				return max;
			else if (val > max)
				return min;
			return val;
		}
	};


	struct KeyCode
	{
		static const char UP_ARROW = 72;
		static const char DOWN_ARROW = 80;
		static const char LEFT_ARROW = 75;
		static const char RIGHT_ARROW = 77;

		static const char ENTER = 13;
		static const char ESCAPE = 27;
	};


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


	static std::vector<Quote*> ListToVector(const std::list<std::unique_ptr<Quote>>& list)
	{
		std::vector<Quote*> destVector;
		destVector.reserve(list.size());

		for (const std::unique_ptr<Quote>& ptr : list)
		{
			if (ptr)
			{
				destVector.push_back(ptr.get());
			}
		}

		return destVector;
	}


	static std::vector<Quote> PtrVectorToValues(const std::vector<Quote*>& vec)
	{
		std::vector<Quote> destVector;
		destVector.reserve(vec.size());

		for (const Quote* ptr : vec)
		{
			destVector.push_back(*ptr);
		}

		return destVector;
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
