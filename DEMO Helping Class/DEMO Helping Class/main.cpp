#include <iostream>  
#include <conio.h>
#include <iomanip>
#include <sstream>

// include our custom class
#include "Account.h" 
#include "Menu.h"
#include "Product.h"
#include "Transaction.h"
#include "Sale.h"
using namespace std; 


void registerAccount();
void loginMenu();

void home(Account user);
Account profile(Account user);
void shop(Account user);
Transaction products(Account user, int category, Transaction cart);

Transaction productDetail(Account user, int productId, Transaction cart);
Transaction cartMenu(Account user, Transaction cart);

void SaleReportMenu(Account user);
 
int productCategorySelection();

int main() {  

	Menu mainmenu;
	mainmenu.header = "Welcome to Demo";
	mainmenu.addOption("Register");
	mainmenu.addOption("Login");
	mainmenu.addOption("Exit"); 

	while (1) {
		switch (mainmenu.prompt())
		{
		case 1:
			registerAccount();
			break;
		case 2:
			loginMenu();
			break;
		case 3:
			return 0;
		default:
			break;
		}
	} 
} 

void registerAccount() {
	Account newacc;

	Menu rgMenu;
	rgMenu.header = "Registration";
	rgMenu.addOption("Username");
	rgMenu.addOption("Password");
	rgMenu.addOption("Email");
	rgMenu.addOption("Year of Birth");
	rgMenu.addOption("Register");
	rgMenu.addOption("Back"); 

	while (1) {

		switch (rgMenu.prompt()) {
		case 1:
			cout << "Insert Username:";
			cin >> newacc.username;
			rgMenu.setValue(0, newacc.username);
			break;
		case 2:
			cout << "Insert password:";
			cin >> newacc.password;
			rgMenu.setValue(1, newacc.password);
			break;
		case 3:
			cout << "Insert email:";
			cin >> newacc.email;
			rgMenu.setValue(2, newacc.email);
			break;
		case 4:
			cout << "Insert yearOfBirth:";
			cin >> newacc.yearOfBirth;
			rgMenu.setValue(3, to_string(newacc.yearOfBirth));
			break;
		case 5:
			newacc.insert();
			return;
		case 6:
			return;
		default:
			break;
		}
	}

}
void loginMenu() {
	Menu loginMenu;
	loginMenu.header = "LOGIN";
	loginMenu.addOption("username");
	loginMenu.addOption("password");
	loginMenu.addOption("Login");
	loginMenu.addOption("Back"); 

	Account user;

	while(1) {
		switch (loginMenu.prompt())
		{
		case 1:
			cout << "Insert Username:";
			cin >> user.username;
			loginMenu.setValue(0, user.username);
			break;
		case 2:
			cout << "Insert Password:";
			cin >> user.password;
			loginMenu.setValue(1, user.password);
			break;
		case 3:
			if (user.login()) {
				home(user);
			}
			else {
				cout << "Invalid Login";
				_getch();
			}
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}


void home(Account user) {
	Menu homeMenu;
	homeMenu.addOption("Profile");
	homeMenu.addOption("Shop");
	homeMenu.addOption("Sale Report");
	homeMenu.addOption("Logout"); 
	while (1) {
		homeMenu.header = "Welcome " + user.username;
		switch (homeMenu.prompt())
		{
		case 1:
			user = profile(user);
			break;
		case 2:
			shop(user);
			break;
		case 3:
			SaleReportMenu(user);
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

Account profile(Account user) {

	Account temp = user; // copy the object

	Menu profileMenu;
	profileMenu.header = "Your profile";
	profileMenu.addOption("username");
	profileMenu.addOption("password");
	profileMenu.addOption("email");
	profileMenu.addOption("yearOfBirth");
	profileMenu.addOption("Reset");
	profileMenu.addOption("Save");
	profileMenu.addOption("Back");
	profileMenu.addOption("Delete Account");

	while (1) {
		profileMenu.setValue(0, temp.username);
		profileMenu.setValue(1, temp.password);
		profileMenu.setValue(2, temp.email);
		profileMenu.setValue(3, to_string(temp.yearOfBirth)); 
		profileMenu.footer = "You are " + to_string(temp.getAge()) + " Years old\nSelect Option";

		switch (profileMenu.prompt())
		{
		case 1:
			cout << "Insert Username:";
			cin >> temp.username;
			break;
		case 2:
			cout << "Insert password:";
			cin >> temp.password;
			break;
		case 3:
			cout << "Insert email:";
			cin >> temp.email;
			break;
		case 4:
			cout << "Insert year of birth:";
			cin >> temp.yearOfBirth;
			break;
		case 5:
			temp = user;
			break;
		case 6:
			user = temp;
			user.update();
			cout << "Updated";
			_getch();  
		case 7:
			return user;
			break;
		case 8:
			cout << "Delete your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') { 
				user = temp;
				user.remove();
				main();
			}

			break;
		default:
			break;
		}
	}
}


void shop(Account user) {
	Transaction cart; //initialize a transaction to hold product values
	cart.user = user.accountId; // put currently logge in user id into the transaction
	
	Menu shopMenu;
	shopMenu.footer = "Select Product Category";
	shopMenu.addOption("Apparel");
	shopMenu.addOption("Food");
	shopMenu.addOption("Furniture");
	shopMenu.addOption("View Cart");
	shopMenu.addOption("Back");
	while (1) {
		shopMenu.header = "SHOP\nItems in cart:" + to_string(cart.count()) + "  \nTotal Price: " + to_string(cart.total());
		switch (shopMenu.prompt())
		{
		case 1:
			cart = products(user, 1,cart);
			break;
		case 2:
			cart = products(user, 2, cart);
			break;
		case 3:
			cart = products(user, 3, cart);
			break;
		case 4: 
			cart = cartMenu(user,cart);
			break;
		case 5:
			return;
			break; 
		}
	}
}

Transaction products(Account user, int category,Transaction cart) {
	vector<Product> products;
	string displayString = "";
	
	string keyWord = "", sortColumn = "price";
	bool ascending = true;
	double minPrice = 0, maxPrice = 999999;
	

	Menu productMenu;
	productMenu.header = "Search Option";
	productMenu.addOption("Key Word");
	productMenu.addOption("Minimum Price");
	productMenu.addOption("Maximum Price");
	productMenu.addOption("Sort By");
	productMenu.addOption("Ordering");
	productMenu.addOption("Search");
	productMenu.addOption("Select");
	productMenu.addOption("Back");

	Menu sortingSubMenu;
	sortingSubMenu.header = "Select Sort category";
	sortingSubMenu.addOption("Price");
	sortingSubMenu.addOption("Name");

	while (1)
	{
		productMenu.setValue(3, sortColumn);
		if (ascending) { 
			productMenu.setValue(4, "Ascending");
		}
		else { 
			productMenu.setValue(4, "Descending");
		}
		
		if (displayString == "") {
			displayString = "\nSearch Result:\n";
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) << "ID" << "|" << setw(20) << "Name" 
				<< "|" << setw(10) << "Price" << "|" << setw(20) << "Description" << "|" << endl;
			for (int i = 0; i < products.size(); i++) {
				tmpString << setw(5) << products[i].productId << "|" << setw(20) << products[i].name 
					<< "|" << setw(10) << products[i].price << "|" << setw(20) << products[i].description << "|" << endl; 
			}
			displayString += tmpString.str();
		}
		productMenu.footer = displayString;

		switch (productMenu.prompt()) {
		case 1:
			cout << "Insert Key Word: ";
			getline(cin, keyWord);
			productMenu.setValue(0, keyWord);
			break;
		case 2:
			cout << "Insert Min Price: ";
			cin >> minPrice;
			productMenu.setValue(1, to_string(minPrice));
			break;
		case 3:
			cout << "Insert Max Price: ";
			cin >> maxPrice;
			productMenu.setValue(2, to_string(maxPrice));
			break;
		case 4:
			switch (sortingSubMenu.prompt())
			{
			case 1:
				sortColumn = "price";
				break;
			case 2:
				sortColumn = "name";
				break;
			}
			break;
		case 5:
			ascending = !ascending; 
			break;
		case 6:
			products = Product::findProduct(category, keyWord, minPrice, maxPrice, sortColumn, ascending);
			displayString = "";
			break;
		case 7:
			cout << "Insert Product Id to Select:";
			int productId;
			cin >> productId;
			cart =  productDetail(user, productId,cart);
			break;
		case 8:
			return cart;
			break;

		}
	};

}

Transaction productDetail(Account user, int productId, Transaction cart) {
	Product product = Product::findProduct(productId);
	if (product.productId == 0) { 
	// default id, which mean product doesn't exist since no 0 id in database
		cout << "Product not found";
		_getch();
		return cart;
	}

	Menu productMenu;
	productMenu.header = "Action:";
	productMenu.addOption("Add to cart");
	productMenu.addOption("Back");
	productMenu.footer = "Product Details:\n"
		"\nName\t: " + product.name
		+ "\nDescription\t: " + product.description
		+ "\nPrice\t: " + to_string(product.price);
	while (1) {
		switch (productMenu.prompt())
		{
		case 1:
			cout << "Insert Quantity :";
			int qty;
			cin >> qty;
			if (qty > 0) {
				cart.addProduct(product, qty);
			}
			cout << endl << "Product Added into cart";
			_getch();
			break;
		case 2:
			return cart;
			break;
		}
	}

}

Transaction cartMenu(Account user, Transaction cart) {
	Menu cartM;
	cartM.header = "Actions";
	cartM.addOption("Checkout");
	cartM.addOption("Empty Cart");
	cartM.addOption("Back");
	stringstream ss;
	ss << fixed << setprecision(2) << setw(20) << "Product|" << setw(20) << "Price|" << setw(20) 
		<< "Quantity|" << setw(20) << "Subtotal|" << endl;
	for (int i = 0; i < cart.items.size(); i++) {
		ss << setw(20) << cart.items[i].first.name << setw(20) << cart.items[i].first.price << setw(20)
			<< cart.items[i].second << setw(20) << (cart.items[i].first.price * cart.items[i].second) << endl;
	}
	ss << setw(20) << "SUM" << setw(20) <<  "" << setw(20) << cart.count() << setw(20) << cart.total();
	cartM.footer = "Cart Items\n" + ss.str();
	char confirm;
	while (1)
	{ 
		switch (cartM.prompt())
		{
		case 1:
			cout << "Check out? (y/n)";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				cart.insert();
				cout << "Transaction saved";
				_getch();
				shop(user); // go back to shop with empty cart
			}
			break;
		case 2:
			cout << "Clear your cart? (y/n)"; 
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') { 
				shop(user); // go back to shop with empty cart
			} 
			break;
		case 3:
			return cart;
		}

	}
}

void SaleReportMenu(Account user) {

	string start, endDate;
		
	vector<int> categoryIds;

	bool sortByDate = true, ascending = true;
	
	Menu saleM; 
	saleM.addOption("Start");
	saleM.addOption("End");
	saleM.addOption("Product Category");
	saleM.addOption("Sort By");
	saleM.setValue(3, "Date");
	saleM.addOption("Order");
	saleM.setValue(4, "Ascending");
	saleM.addOption("Generate");
	saleM.addOption("Back");

	vector<Sale> result; // vector to store the result

	// we declare it like this so that the index matches their id in the database
	string categoryNames[] = {"None","Apparel","Food","Furniture"};

	//declare outside so that we don't unnecesarily declare new variable in each loop iteration
	string selectedCategoryName;
	int tmpSelectedCategory;

	vector<int>::iterator iterator; //iterator is declare using what we are iterating, in this case it is vector of integer

	while (1)
	{

		selectedCategoryName = "";
		if (categoryIds.empty()) {
			selectedCategoryName = "NONE";
		}
		else {
			for (int i = 0; i < categoryIds.size(); i++) {
				selectedCategoryName += categoryNames[categoryIds[i]] + ", ";
			}
		}
		saleM.setValue(2, selectedCategoryName);



		// report display
		stringstream ss;
		// construct our report header
		ss << endl <<"--- SALES REPORT ---" <<endl<< "|" << setw(20) << "Date Time" << "|";
		if (!categoryIds.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "Category" << "|";
		}	
		ss << setw(20) << "Sale" << "|";

		double totalSale = 0;
		// repeat same structure for content of the report
		for (int i = 0; i < result.size(); i++) {
			ss << endl << "|" << setw(20) << result[i].date.substr(0,7) << "|";
			if (!categoryIds.empty()) {
				// if category id not empty we add category column
				ss << setw(20) << result[i].categoryName << "|";
			}
			ss << setw(20) << result[i].value << "|";
			totalSale += result[i].value;

		}

		ss << endl << "|" << setw(20) << "Total Sale" << "|";
		if (!categoryIds.empty()) {
			// if category id not empty we add category column
			ss << setw(20) << "" << " ";
		}
		ss << setw(20) << totalSale << "|";

		ss << endl << "--- END OF REPORT ---" << endl;
		saleM.header = ss.str();
		 

		switch (saleM.prompt())
		{
		case 1:
			cout << "Inser start date (yyyy-mm-dd): ";
			cin >> start;
			saleM.setValue(0, start);
			break;
		case 2:
			cout << "Inser end date (yyyy-mm-dd): ";
			cin >> endDate;
			saleM.setValue(1, endDate);
			break;
		case 3: //toggle category
			tmpSelectedCategory = productCategorySelection();

			//find the selcted category id inside our categoryIds vector
			 iterator= find(categoryIds.begin(), categoryIds.end(), tmpSelectedCategory);

			if (iterator == categoryIds.end()) {//if the iterator reaches the end means not found
				categoryIds.push_back(tmpSelectedCategory);
			}
			else {
				categoryIds.erase(iterator); //if it exist erase it
			}
			
			break;
		case 4:// sort by
			sortByDate = !sortByDate;
			if(sortByDate)
				saleM.setValue(3, "Date");
			else
				saleM.setValue(3, "Price");
			break;
		case 5:
			ascending = !ascending;
			if(ascending)
				saleM.setValue(4, "Ascending");
			else
				saleM.setValue(4, "Descending");
			break;
		case 6:
			result.clear(); 
				result = Sale::salesReport(start, endDate, categoryIds, sortByDate, ascending); 
			break;
		case 7:
			return;
			break;
		}

	}

}
 
int productCategorySelection() {
	Menu categoryMnu;
	categoryMnu.header = "TOGGLE CATEGORY";
	categoryMnu.addOption("Apparel");
	categoryMnu.addOption("Food");
	categoryMnu.addOption("Furniture");
	while (1)
	{
		//since the selected option starts from 1
		// and our category id also is 1:apparel, 2:Food, 3:Furniture
		// we can just use the value of the prompt
		// if your database id and the prompt result does not match you might need to modify the return value first
		return categoryMnu.prompt();

	}
} 