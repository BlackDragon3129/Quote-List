#pragma once

#include <Windows.h>
#include <shlobj.h>
#include <string>
#include <iostream>
#include <fstream> 
#include <locale>
#include <codecvt>


namespace QuoteList
{
	struct FileSystem
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


		static void CreateFolder(const wchar_t* path)
		{
			SHCreateDirectoryExW(NULL, path, NULL);
		}


		static void WriteFile(const wchar_t* targetPath, const wchar_t* data)
		{
			CreateFolder(targetPath);

			std::wofstream saveFile;
			saveFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

			saveFile.open(targetPath);

			if (saveFile.is_open())
			{
				saveFile << data;
			}

			saveFile.close();
		}


		static std::wstring ReadFile(const wchar_t* targetPath)
		{
			std::wifstream file(targetPath);
			file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

			std::wstring data = L"";

			std::wstring line;
			if (file.is_open())
			{
				while (std::getline(file, line))
				{
					data.append(line + L'\n');
				}
			}
			else
			{
				return L"";
			}
		}
	};
}
