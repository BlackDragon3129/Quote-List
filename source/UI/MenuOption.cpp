#include <UI/MenuOption.hpp>
#include <BaseLibrary.hpp>


using namespace QuoteList::UI;


MenuOption::MenuOption(const char* name, const unsigned char& x, const unsigned char& y,
	const Function& action)
{
	Name = name;
	X = x;
	Y = y;
	Action = action;
}

void MenuOption::CallAction() const
{
	if (Action)
		Action();
}
