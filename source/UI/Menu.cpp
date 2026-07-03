#include <UI/Menu.hpp>
#include <BaseLibrary.hpp>

using namespace QuoteList::UI;


Menu::Menu(const char* name)
{
	m_name = name;
	m_currentOptionIndex = 0;
}


void Menu::AddOption(MenuOption& newOption)
{
	m_options.push_back(newOption);
}


void Menu::ChangeCurrentOption(const int& change)
{
	m_currentOptionIndex = Math::ClampReverse
	(
		(int)(m_currentOptionIndex + change),
		0,
		(int)(m_options.size() - 1)
	);

	Draw();
}


void Menu::Draw() const
{
	system("cls");

	// Menu's name output
	std::cout << m_name;

	// Options output
	for (std::size_t i = 0; i < m_options.size(); i++)
	{
		// Arrow output
		if (m_currentOptionIndex == i)
		{
			CursorGotoXY(0, 2 + i);
			std::cout << ">";
		}

		// Option name output
		CursorGotoXY(2, 2 + i);
		std::cout << m_options.at(i).Name;
	}
}


void Menu::OptionAct()
{
	m_options.at(m_currentOptionIndex).CallAction();
}
