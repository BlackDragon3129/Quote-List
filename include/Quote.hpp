#pragma once

#include <iostream>


namespace QuoteList
{
	struct Quote
	{
		std::string Content, Author, Source;

		Quote(const std::string& content, const std::string& author = "", 
			const std::string& source = "");

		void Print() const;
	};
}
