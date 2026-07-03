#include <UI/MenuVariant.hpp>
#include <BaseLibrary.hpp>


using namespace QuoteList::UI;


MenuVariant::MenuVariant(const char* name, const unsigned char& x, const unsigned char& y,
	const Function& action)
{
	Name = name;
	X = x;
	Y = y;
	Action = action;
}

void MenuVariant::CallAction() const
{
	if (Action)
		Action();
}
