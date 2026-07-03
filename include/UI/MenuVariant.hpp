#pragma once
#include <functional>

#include <BaseLibrary.hpp>


namespace QuoteList
{
	namespace UI
	{
		struct MenuVariant
		{
			const char* Name;
			unsigned char X, Y;
			Function Action;

			MenuVariant(const char* name, const unsigned char& x, const unsigned char& y,
				const Function& action);

			void CallAction() const;
		};
	}
}