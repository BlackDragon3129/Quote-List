#pragma once

#include <iostream>


namespace QuoteList
{
	struct FileSystem
	{
		static std::wstring GetAppDataPath();


		static void CreateFolder(const wchar_t* path);


		static void WriteFile(std::wstring targetPath, const std::wstring& fileName,
			const wchar_t* data);


		static std::wstring ReadFile(const wchar_t* targetPath);
	};
}
