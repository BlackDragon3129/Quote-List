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
			Menu* m_previousMenu;
			std::vector<MenuOption> m_options;
			const std::wstring m_name;
			unsigned int m_currentOptionIndex;
			bool m_opened, m_paused;

		public:
			Menu(const std::wstring& name, Menu* previousMenu = nullptr);

			void AddOption(MenuOption& newOption);
			void ChangeCurrentOption(const int& change);
			void Draw(const bool& clearConsole = true) const;
			void OptionAct();

			void Open(const bool& clearConsole = true);
			void Close(const bool& openPrevious = true);
			void Pause();
		};
	}
}
