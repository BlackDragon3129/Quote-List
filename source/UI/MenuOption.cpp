#include <UI/MenuOption.hpp>
#include <BaseLibrary.hpp>


using namespace QuoteList::UI;


MenuOption::MenuOption(const wchar_t* name, const Function& action)
{
	Name = name;
	Action = action;
}

void MenuOption::CallAction() const
{
	if (Action)
		Action();
}
