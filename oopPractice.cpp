#include <iostream>
#include "Quote.h"
using namespace std;

void oop_practice() {
	Quote q("20180223-1", 10);
	cout << endl;
	Bulk_quote bq(q);
	cout << endl;
	Bulk_quote bq2("20180223-2", 10, 2, 0.05);
	cout << endl;
	Quote q2(bq2);  //slice down
	cout << endl;
	Bulk_quote bq3(bq2);
	cout << endl;
	/*print_total(cout, q, 10);
	cout << endl;
	print_total(cout, bq, 10);
	cout << endl;
	print_total(cout, bq2, 10);
	cout << endl;
	print_total(cout, q2, 10);
	cout << endl;*/
	Basket basket;
	basket.add_item(q);
	cout << endl;
	basket.add_item(std::move(q2));
	cout << endl;
	basket.add_item(bq);
	cout << endl;
	basket.add_item(std::move(bq2));
	cout << endl;
	basket.add_item(shared_ptr<Quote>(&bq3));
	cout << endl;
	//q2 is a Quote and is the first of "20180223"
	//Quote::net_price is called when calculating "20180223"
	basket.total_receipt(cout);
}