#include "Menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

Menu::Menu() {
	header = "";
	footer = "Select option";
	bullet = "-";

}
int Menu::prompt() {
	int selected = -1;
	do
	{ 
		system("cls"); // clear ur console
		cout << header << endl;
		for (int i = 0; i < options.size(); i++) {//loop trhough each option 
			cout << i+1 << bullet << options[i].first;
			if (options[i].second != "") {
				cout << " : " << options[i].second;
			}
			cout << endl;
		}
		cout << footer << endl;

		selected = _getch() - '0'; 
	} while (selected < 1 || selected > options.size());
	return selected;
}
void Menu::addOption(string option) {
	options.push_back({ option,"" });
}
void Menu::setValue(int index,string value) {
	if (index >= 0 && index < options.size()) {
		options[index].second = value;
	}
}
Menu::~Menu() {
	options.clear();
}