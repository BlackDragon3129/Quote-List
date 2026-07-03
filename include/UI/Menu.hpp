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
			unsigned int m_currentOptionIndex;
			bool m_opened;

		public:
			Menu(const char* name);

			void AddOption(MenuOption& newOption);
			void ChangeCurrentOption(const int& change);
			void Draw() const;
			void OptionAct();

			void Open();
		};
	}
}
