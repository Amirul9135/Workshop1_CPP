#include "Sale.h"
using namespace std;
using namespace sql;

Sale::Sale(ResultSet* data) {
	value = data->getDouble("value");
	date = data->getString("date");
	categoryName = data->getString("categoryName");
} 


vector<Sale> Sale::salesReport(string start, string end, vector<int> categoryIds, bool sortByDate, bool ascending) {
	/*
	this is the query which we will be using, 
	but we will dynamicaly generate it to make this method reusable for multiple report

	SELECT t.dateTime as date,pc.name as categoryName , SUM(p.price * ti.quantity) as value 
		FROM transaction t 
		JOIN transaction_item ti ON t.transactionId = ti.transactionId
		JOIN product p ON p.productId = ti.productId 
		JOIN product_category pc ON  pc.categoryId = p.category AND p.category IN (?,?)
		WHERE t.dateTime >= ? AND t.dateTime <= ?
		GROUP BY p.category, CAST(MONTH(t.dateTime) AS VARCHAR(2)) + '-' + CAST(YEAR(t.dateTime) AS VARCHAR(4))
		ORDER BY value ASC

	
	*/

	 
	string categoryString = "";
	if (categoryIds.size() > 0) {
		categoryString = " AND p.category IN (";
		for (int i = 0; i < categoryIds.size(); i++) {
			categoryString += "?,";
		}
		// since we add , after each placeholder we now have extra comma at the end
		categoryString.erase(categoryString.size() - 1); //remove the character at the end 
		categoryString += ") "; //  close bracket   

	}
	// categoryIds wil also be used as condition but since 


	// construct our query for the table and joins part first
	string sql = " SELECT t.dateTime as date, pc.name as categoryName, SUM(p.price * ti.quantity) as value "
		" FROM transaction t "
		" JOIN transaction_item ti ON t.transactionId = ti.transactionId "
		" JOIN product p ON p.productId = ti.productId "
		" JOIN product_category pc ON  pc.categoryId = p.category "
		+ categoryString; // append category string which will be our join condition if cateogryId vector is not empty 
						  // whereby if the categoryIds is empty this will simply be appending empty string that changes nothing

	// add the where clause 
	sql += " WHERE  t.dateTime >= ? AND t.dateTime <= ? ";
	 
	// now construct our grouping
	sql += " GROUP BY ";
	if ( ! categoryIds.empty()) {
		// if categoryids is not empty only we group by category
		sql += " p.category, ";
	}
	// otherwise we skip the p.category to only groups it by its year and month
	sql += " CAST(MONTH(t.dateTime) AS VARCHAR(2)) + '-' + CAST(YEAR(t.dateTime) AS VARCHAR(4)) ";
	         //    10-2023

	// now construct the sorting clause
	sql += " ORDER BY  ";
	if (sortByDate) {
		// we have bool sortByDate parameter, if this value is true then we use date column for ordering
		sql += " t.dateTime ";
	}
	else {
		// otherwise we use the result column sale for ordering
		sql += " value ";
	}

	// finally the ordering direction determined using boolean ascending
	if (ascending) {
		sql += " ASC ";
	}
	else {
		sql += " DESC ";
	}
	 
	// declare vector > execute query > return result in vector 
	vector <Sale> salesReport;

	DBConnection db; 

	db.prepareStatement(sql);
	// since we have non-fixed number of placeholder ? in our prepared statment we need to use a varaible to keep track of the index

	int index = 1; // start from 1
	// load the value for category ids
	while (index <= categoryIds.size()) {
		// remember our index starts from 1 to follow prepared statement indexing
		// thus, our exit condition is until the vector size
		
		db.stmt->setInt(index, categoryIds[index - 1]); // and we -1 to access the item in the vector since vector index starts from 0
		index++;
	}
	// after the loop we have the latest index value ready to be use for our where condition placehoders (?)
	// if categoryIds is empty, size 0 the previous loop will not occur and index here is still 1 so it will still be correct
	db.stmt->setString(index, start);
	index++;//move index forward
	db.stmt->setString(index, end);
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Sale tmpSale(db.res);
			salesReport.push_back(tmpSale);

		}
	}

	db.~DBConnection();
	return salesReport;
}


// in Sale.h we have already give destructor ~Sale() so we do not need to define it in this file