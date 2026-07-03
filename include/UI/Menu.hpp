#pragma once
#include <vector>

#include <UI/MenuOption.hpp>
#include <BaseLibrary.hpp>


namespace QuoteList
{
	namespace UI
	{
		class Menu
		{
			std::vector<MenuOption> m_options;
			const char* m_name;
			unsigned int m_currentOption;

		public:
			Menu(const char* name);

			void AddOption(const MenuOption& newOption);
			void ChangeCurrentOption(const int& change);
			void Draw() const;
			void OptionAct();
		};
	}
}
