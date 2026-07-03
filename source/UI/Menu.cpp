#include <UI/Menu.hpp>
#include <BaseLibrary.hpp>
#include <conio.h>

using namespace QuoteList::UI;


Menu::Menu(const char* name, Menu* previousMenu)
{
	m_name = name;
	m_currentOptionIndex = 0;
	m_opened = false;
	m_previousMenu = previousMenu;
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


void Menu::Open()
{
	if (m_previousMenu != nullptr)
	{
		m_previousMenu->Close();
	}

	m_opened = true;

	Draw();

	// Input loop
	while (m_opened)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
				// Up movement
			case 'W':
			case 'w':
			case KeyCode::UP_ARROW:
				ChangeCurrentOption(-1);
				break;

				// Down movement
			case 'S':
			case 's':
			case KeyCode::DOWN_ARROW:
				ChangeCurrentOption(1);
				break;

				// Option action call
			case KeyCode::ENTER:
				OptionAct();
				break;

				// Exit
			case KeyCode::ESCAPE:
				m_opened = false;
				break;
			}
		}
	}
}
void Menu::Close()
{
	if (m_previousMenu != nullptr)
	{
		m_previousMenu->Open();
	}
	m_opened = false;
}
