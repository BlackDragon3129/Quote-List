#include <UI/Menu.hpp>
#include <Library/LibrariesRoot.hpp>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

using namespace QuoteList::UI;


Menu::Menu(const std::wstring& name, Menu* previousMenu) : m_name(name)
{
	m_currentOptionIndex = 0;
	m_paused = m_opened = false;
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


void Menu::Draw(const bool& clearConsole) const
{
	if (clearConsole)
	{
		system("cls");
	}

	// Menu's name output
	std::wcout << m_name;

	// Options output
	for (std::size_t i = 0; i < m_options.size(); i++)
	{
		// Arrow output
		if (m_currentOptionIndex == i)
		{
			Console::CursorGotoXY(0, 2 + i);
			std::wcout << ">";
		}

		// Option name output
		Console::CursorGotoXY(2, 2 + i);
		std::wcout << m_options.at(i).Name;
	}
}


void Menu::OptionAct()
{
	try
	{
		m_options.at(m_currentOptionIndex).CallAction();
	}
	catch (std::out_of_range) {}
}


void Menu::Open(const bool& clearConsole)
{
	if (m_previousMenu != nullptr)
	{
		m_previousMenu->Pause();
	}

	m_paused = false;
	m_opened = true;

	Draw(clearConsole);

	// Input loop
	while (m_opened && !m_paused)
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
				Close();
				break;
			}
		}
	}
}
void Menu::Close(const bool& openPrevious)
{
	m_paused = m_opened = false;
	if (openPrevious && m_previousMenu != nullptr)
	{
		m_previousMenu->Open();
	}
}
void Menu::Pause()
{
	m_paused = true;
}
