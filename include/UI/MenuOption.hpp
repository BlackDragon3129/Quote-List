#pragma once
#include <functional>

#include <BaseLibrary.hpp>


namespace QuoteList
{
	namespace UI
	{
		struct MenuOption
		{
			const wchar_t* Name;
			Function Action;

			MenuOption(const wchar_t* name, const Function& action);

			void CallAction() const;
		};
	}
}