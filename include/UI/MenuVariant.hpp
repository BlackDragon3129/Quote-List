#pragma once
#include <functional>




namespace QuoteList
{
	namespace UI
	{
		struct MenuVariant
		{
			const char* Name;
			unsigned char X, Y;
			Function Action;

			MenuVariant()
		};
	}
}