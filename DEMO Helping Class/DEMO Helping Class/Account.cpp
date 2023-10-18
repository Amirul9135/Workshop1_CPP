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
