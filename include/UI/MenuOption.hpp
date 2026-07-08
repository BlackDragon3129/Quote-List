#pragma once
#include <functional>

#include <Library/LibrariesRoot.hpp>


namespace QuoteList
{
	namespace UI
	{
		struct MenuOption
		{
			const std::wstring Name;
			Function Action;

			MenuOption(const std::wstring& name, const Function& action);

			void CallAction() const;
		};
	}
}