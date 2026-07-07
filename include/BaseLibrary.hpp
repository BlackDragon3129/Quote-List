#pragma once
#include <Windows.h>
#include <shlobj.h>
#include <string>
#include <iostream>
#include <functional>
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
