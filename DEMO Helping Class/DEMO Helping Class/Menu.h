#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <utility>

class Menu
{
public:
	std::string header,footer,bullet;
	Menu();
	void addOption(std::string option);
	void setValue(int index,std::string value);
	int prompt();
	~Menu();
private:
	std::vector<std::pair<std::string,std::string>> options;
	// [ {"1","2"}  ,{"1","2"}  ]
};


#endif