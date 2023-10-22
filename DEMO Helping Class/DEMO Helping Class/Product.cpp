#include "Product.h"
#include <vector> 
using namespace std;

Product::Product() {
	productId = 0;
	category = 0;
	name = "";
	description = "";
	price = 0;
}

Product::Product(sql::ResultSet* data) {
	productId = data->getInt("productId");
	name = data->getString("name");
	description = data->getString("description");
	price = data->getDouble("price");
	category = data->getInt("category");
}

vector<Product> Product::findProduct(int category, string keyword, double minPrice,
	double maxPrice, string sortColumn, bool ascending) {

	string query = "SELECT * FROM `product` WHERE " 
		 " (name LIKE ? OR description LIKE ?) AND price >= ? AND price <= ? AND category = ? "
		 " ORDER BY " + sortColumn;
	if (ascending) {
		query += " ASC";
	}
	else {
		query += " DESC";
	}
	// 
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");   
	db.stmt->setString(2, "%" + keyword + "%");
	db.stmt->setDouble(3,minPrice);
	db.stmt->setDouble(4, maxPrice);
	db.stmt->setInt(5, category);

	vector<Product> products;

	db.QueryResult();

	if (db.res->rowsCount()> 0) {

		while (db.res->next()) {
			Product tmpProduct(db.res);
			products.push_back(tmpProduct);

		}
	}

	db.~DBConnection();
	return products;
}


Product Product::findProduct(int productId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM product WHERE productId=?");
	db.stmt->setInt(1, productId);
	db.QueryResult();

	Product result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			Product found(db.res); 
			result = found; 
		}
	}
	db.~DBConnection();
	return result;
}
 
Product::~Product() {

}