#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
public://access specifier
	int accountId, yearOfBirth; //numerical attributes
	std::string username, email; // text attributes
	 


	Account(); // constructor method
	Account(int accountId, int yearOfBirth, std::string username, std::string password, std::string email);

	bool login(); 
	void insert();
	void update();
	void remove();
	int getAge();  

	~Account(); //destructor method


	static Account older(Account a, Account b);



	// getter setter for password
	void setPassword(std::string pass);
	std::string getPassword();

	// to check if a string matches with the encrypted password
	bool MatcPasswordWith(std::string plainText);

private:
	std::string password; //encapsulate password inside private because we want to ensure it is encrypted when set
	std::string encrypt(std::string input);
	char toChar(int asciDecimal);
	bool isMatch(std::string encrypted, std::string testText);
	 
};

#endif

