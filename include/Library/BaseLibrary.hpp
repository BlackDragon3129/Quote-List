#pragma once
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
