#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include "DBConnection.h"

class Product
{
public:
	int productId, category;
	std::string name, description;
	double price;

	Product(); 
	Product(sql::ResultSet* data); 

	~Product();

	static Product findProduct(int productId);

	static std::vector<Product> findProduct(int category, std::string keyword,double minPrice,
		double maxPrice, std::string sortColumn, bool ascending);

};


#endif