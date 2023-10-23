#include "ArrowMenu.h"
#include <iostream>
#include <conio.h>
using namespace std;

ArrowMenu::ArrowMenu() {
	footer = "Use Up/Down key to move selection and press enter to select";
	separator = "---------------------------------------------------";
	bullet = ">";
}

int ArrowMenu::prompt(int selected) {
	// selected is the optional paramter, by default if no value is passed we assume the initial selection is at index 0, the first item
	char option = '\0';
	while (1) {

		system("cls");
		cout << header << endl << separator << endl;

		for (int i = 0; i < items.size(); i++) {
			if (selected == i) {
				cout << "\u001b[33m"; //if it is selected option we set the console text color to yellow/gold
			}
			cout << bullet << items[i].first;
			if (items[i].second.length() > 0) {
				cout << " : " << items[i].second;
			}
			cout <<  endl;
			if (selected == i) {
				cout << "\u001b[0m"; // this code reset backs the color to default colouring
			}
		}

		cout << separator << endl << footer << endl ;
		option = _getch();

		//cast the character returned by getch to int which will be its ASCII code
		if (int(option) == -32) { 
			//-32 is the first ASCII code sent to buffer to indicate escape character for special character. 
			// this is necessary since without the escape character some special character such as arrow keys overlaps with normal character ASCII
			// -32 is sent first to input bufer, which mean for special character there are actually character sent to buffer
			// so we need to getch one more time to capture the actual character for the key being pressed
			option = _getch();
			switch (option)
			{
			case 72: // 72 is the ASCII code for up arrow
				if (selected > 0) {
					// iff selected is greater than 0 and up arrow is pressed we decrease the selected index
					selected--;
				}
				else{
					selected = items.size() - 1; //if we can't decreament when user already at first item we move selection to last instead
				}
				break;
			case 80: // 80 is the ASCII code for down arrow
				if (selected < items.size() - 1) {
					// if selected is less than lass index we increment
					selected++;
				}
				else {
					selected = 0; // if we can't increment means that it is last item, we move selected back to the top
				}
				break;
			}
		}
		else {
			// if the frst character sent to buffer after getch is not -32 means that it is normal character so we can process accordingly
			if (option == 27) { 
				// 27 is the ASCII code for "ESCAPE"
				// when user press escape we exit from the loop and just return -1 to indicate user cancel selection
				return -1;

			}
			else if (option == '\r') {
				// we can also compare the integer with character like this, \r is carriage return aka enter
				// when enter is pressed we assume user want to proceed, so we return the selected
				return selected;

			}
		}
	} 

}

void ArrowMenu::addOption(string text, string value) {
	items.push_back({ text,value });
}

void ArrowMenu::clearOption() {
	items.clear();
}
void ArrowMenu::setValue(int index, string value) {
	if (index > 0 && index < items.size()) {
		items[index].second = value;
	}
}