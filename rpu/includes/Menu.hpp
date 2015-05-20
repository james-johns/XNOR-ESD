

#ifndef _MENU_HPP_
#define _MENU_HPP_

class Menu {
public:
	Menu();
	~Menu();

	void up();
	void down();

	const char *getCurrentMenuItem();
	signed int getCurrentSelected() { return curIndex; }

	const char *getMenuItem(unsigned int index);
	void addMenuItem(const char *str);
private:
	std::vector<std::string *> list;
	signed int curIndex;
};

#endif
