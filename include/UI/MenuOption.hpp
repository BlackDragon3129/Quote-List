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
			unsigned char X, Y;
			Function Action;

			MenuOption(const char* name, const unsigned char& x, const unsigned char& y,
				const Function& action);

			void CallAction() const;
		};
	}
}