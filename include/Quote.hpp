#pragma once

#include <iostream>


namespace QuoteList
{
	struct Quote
	{
		std::string Author, Source;

		Quote();
		Quote(const std::string& author);
		Quote(const std::string& author, const std::string& source);
	};
}
