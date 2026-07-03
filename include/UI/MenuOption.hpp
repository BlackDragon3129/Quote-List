#pragma once
#include <functional>

#include <BaseLibrary.hpp>


namespace QuoteList
{
	namespace UI
	{
		struct MenuOption
		{
			const char* Name;
			Function Action;

			MenuOption(const char* name, const Function& action);

			void CallAction() const;
		};
	}
}