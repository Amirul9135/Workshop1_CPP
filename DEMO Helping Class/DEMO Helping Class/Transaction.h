#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include "Product.h"

class Transaction
{
public:
	std::string dateTime;
	int transactionId, user;
	std::vector<std::pair<Product,int>> items; // pair of product and its quantity

	Transaction();  
	void addProduct(Product product, int quantity);
	void insert();
	double total();
	int count();
};


#endif