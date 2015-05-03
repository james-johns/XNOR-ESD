

#include <vector>
#include <string>

#include <Menu.hpp>

Menu::Menu()
{
	curIndex = 0;
	list.clear();
}

Menu::~Menu()
{
	for (std::vector<std::string *>::iterator it = list.begin();
	     it != list.end(); it++) {
		delete *it;
	}
}

void Menu::up()
{
	curIndex--;
	if (curIndex < 0)
		curIndex = 0;
}

void Menu::down()
{
	curIndex++;
	if (curIndex >= list.size())
		curIndex = list.size()-1;
}

const char *Menu::getCurrentMenuItem()
{
	return list[curIndex]->c_str();
}

const char *Menu::getMenuItem(unsigned int index)
{
	if (index < list.size())
		return list[index]->c_str();
	else
		return NULL;
}

void Menu::addMenuItem(const char *str)
{
	std::string *s = new std::string(str);
	list.push_back(s);
}

