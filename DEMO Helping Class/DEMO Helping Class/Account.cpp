#include "Account.h"
#include <ctime>
#include "DBConnection.h" 
using namespace std;

Account::Account() {
	//initialize
	accountId = 0;
	yearOfBirth = 0;
	username = "";
	password = "";
	email = "";
}
Account::Account(int accountId, int yearOfBirth, std::string username, std::string password, std::string email) { 
	this->accountId = accountId;
	this->yearOfBirth = yearOfBirth;
	this->username = username;
	this->password = password;
	this->email = email;
}
bool Account::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM account WHERE username=? AND password=?");
	// here we do password matching in database where we pass user input password into query
	// THIS IS ONLY DOABLE HERE BECAUSE WE ARE USING SUPER SIMPLE ENCRYPTION
	// ADVANCED ENCRYPTION CRYPTOGRAPHY WILL NEED YOU TO QUERY THE PASSWORD BY USERNAME OUT OF THE DATBASE
	// USING THE PASSWORD QUERIED OUT FROM DATABASE, MATCH IT USING THE ALGORITHM
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			accountId = db.res->getInt("accountId");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
			yearOfBirth = db.res->getInt("yearOfBirth");
		}
		db.~DBConnection();
		return true;
	} 
	else {

		db.~DBConnection();
		return false;
	} 
}
void Account::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into account (username,password,email,yearOfBirth) VALUES (?,?,?,?)");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, email);
	db.stmt->setInt(4, yearOfBirth);
	db.QueryStatement();
	db.~DBConnection();
}
void Account::update() {

	DBConnection db;
	db.prepareStatement("UPDATE account SET username=?, password=?, email=?,yearOfBirth=? WHERE accountId=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, email);
	db.stmt->setInt(4, yearOfBirth);
	db.stmt->setInt(5, accountId);
	db.QueryStatement();
	db.~DBConnection();

}
void Account::remove() { 
	DBConnection db;
	db.prepareStatement("DELETE FROM account WHERE accountId=?");
	db.stmt->setInt(1, accountId);
	db.QueryStatement();
	db.~DBConnection();
}
int Account::getAge() {
	if (yearOfBirth == 0) {
		return 0;
	}
	time_t current = time(0); // get time in epoch seconds (since 1900)
	tm now; // create a struct/object of tm to hold data
	localtime_s(&now, &current); //populate the now object with data from current

	return (now.tm_year + 1900) // +1900 to the epoch year to get current year
		- yearOfBirth; // minus user year of birth to get their age
}



Account::~Account() {

}


Account Account::older(Account a, Account b) {
	if (b.getAge() > a.getAge()) {
		return b;
	}
	return a;
}


// getter setter for password
// since password is private, only way to change value from outside is via this function
// which will encrypt the string 
void Account::setPassword(string pass) {
	password = encrypt(pass);

}
string Account::getPassword() {
	return password;
}

// to check if a string matches with the encrypted password
bool Account::MatcPasswordWith(string plainText) {
	return isMatch(password, plainText);
}


// simple shifting encryption where the character are shifted by its ASCII decimal code depending on its index
string Account::encrypt(string input) {
	string ciphertext = "";
	for (int i = 0; i < input.length(); i++) {
		ciphertext += toChar(input[i] + ((i ^ 2 + 1) * input.length()));
	}
	return ciphertext;
}

// since we are using our own simple encryption, just re ecnrypt the target plain text and compare with the encrypted text
bool Account::isMatch(string encrypted, string testText) {
	return (bool)(encrypt(testText) == encrypted);
}

char Account::toChar(int asciDecimal) {
	// convert int to reeadbale char based on ASCII
	// characters in ASCII decimal are 32 (space) ~ 125 (~)
	while (asciDecimal < 33) {
		asciDecimal = asciDecimal + asciDecimal + 1;
	}
	while (asciDecimal > 125) {
		asciDecimal = (asciDecimal % 125) + 32;
	}
	return (char)asciDecimal;
}
