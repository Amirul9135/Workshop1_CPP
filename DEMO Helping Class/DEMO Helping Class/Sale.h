#pragma once
#ifndef SALE_H
#define SALE_h

#include <string>
#include <vector>
#include "DBConnection.h"

class Sale
{
public:
	std::string date, categoryName;
	double value;

	Sale(sql::ResultSet* data);
	//since sale data is computed from database, it does not need normal constructor
	//it will not exist without result set 


	static std::vector<Sale> salesReport(std::string start, std::string end, std::vector<int> categoryIds,bool sortByDate, bool ascending);


	~Sale() {/*you can also define blank/simple method here,
		since we do not have anything to do in destructor yet
		we just declare empty method here*/
	};
};


#endif