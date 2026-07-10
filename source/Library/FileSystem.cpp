#include <Library/FileSystem.hpp>

#include <Windows.h>
#include <shlobj.h>
#include <string>
#include <iostream>
#include <fstream> 
#include <locale>
#include <codecvt>


using namespace QuoteList;


std::wstring FileSystem::GetAppDataPath()
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


void FileSystem::CreateFolder(const wchar_t* path)
{
	SHCreateDirectoryExW(NULL, path, NULL);
}


bool FileSystem::Exists(const wchar_t* path)
{
	return std::wifstream(path).good();
}


void FileSystem::WriteFile(std::wstring targetPath, const std::wstring& fileName,
	const wchar_t* data)
{
	if (targetPath.back() != L'\\')
	{
		targetPath.push_back(L'\\');
	}

	CreateFolder(targetPath.c_str());

	std::wofstream saveFile;
	saveFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	saveFile.open(targetPath + fileName);

	if (saveFile.is_open())
	{
		saveFile << data;
	}

	saveFile.close();
}


std::wstring FileSystem::ReadFile(const wchar_t* targetPath)
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

	return data;
}
