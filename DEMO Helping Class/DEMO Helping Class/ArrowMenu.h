#pragma once 
#ifndef ARROWMENU_H
#define ARROWMENU_H

/*
* this class will handle displaying menu which is navigable using the arrow keys 
*/





#include <string>
#include <vector>
#include <utility>
class ArrowMenu
{
public:
	std::string header, footer, bullet, separator; 
	// separator will be used to divide headder footer and the options. since it is attribute it can be modified --- is only the default value

	std::vector<std::pair<std::string, std::string>> items;
	// first part of the pair will be the text, second part is value if any

	void addOption(std::string option,std::string value = "");
	void setValue(int index, std::string text);
	void clearOption();


	ArrowMenu();
	int prompt(int = 0);
};

#endif
