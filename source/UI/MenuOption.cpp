#include <UI/MenuOption.hpp>
#include <BaseLibrary.hpp>


using namespace QuoteList::UI;


MenuOption::MenuOption(const std::wstring& name, const Function& action) : Name(name)
{
	Action = action;
}

void MenuOption::CallAction() const
{
	if (Action)
		Action();
}
