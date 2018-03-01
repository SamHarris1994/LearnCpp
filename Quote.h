#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <iostream>
#include <string>
#include <memory>
#include <set>
using namespace std;

class Quote {
	string bookNo;
protected:
	double price = 0.0;
public:
	Quote() = default;
	Quote(const string &book, double p): bookNo(book), price(p) {
		cout << "Quote constructor is running" << endl;
	}
	Quote(const Quote &q): bookNo(q.bookNo), price(q.price) {       //copy constructor
		cout << "Quote copy constructor is running" << endl;
		this->debug();
	}
	Quote(Quote &&q) noexcept: bookNo(q.bookNo), price(q.price) {}  //move constructor
	string isbn() const { return bookNo; }
	virtual void debug() {
		cout << "bookNo = " << bookNo << ", price = " << price << endl;
	}
	virtual double net_price(size_t n) const { return n*price; }
	virtual Quote *clone() const & { return new Quote(*this); }
	virtual Quote *clone() && { return new Quote(std::move(*this)); }
	virtual ~Quote() = default;
};

class Disc_quote : public Quote {  //abstract class
protected:
	double discount = 0.0;
public:
	Disc_quote() = default;
	Disc_quote(const string &book, double p, double disc):
		Quote(book, p), discount(disc) {
		cout << "Disc_quote constructor is running" << endl;
	}
	Disc_quote(const Disc_quote &dq): Quote(dq), discount(dq.discount) {
		cout << "Disc_quote copy constructor is runing" << endl;
		this->debug();
	}
	Disc_quote(Disc_quote &&dq) noexcept: Quote(std::move(dq)), discount(dq.discount) {}
	Disc_quote(const Quote &q) : Quote(q) {
		cout << "Disc_quote another copy constructor is runing" << endl;
		this->debug();
	}
	virtual void debug() {
		Quote::debug();
		cout << "discount = " << discount << endl;
	}
	//pure virtual function (can't construct Disc_Quote instance)
	double net_price(size_t n) const = 0;
};

class Bulk_quote : public Disc_quote {
	size_t min_qty = 0;
public:
	using Disc_quote::Disc_quote;  //inherit constructor (can be overrided)
	Bulk_quote() = default;
	Bulk_quote(const string &book, double p, size_t qty, double disc):
		Disc_quote(book, p, disc), min_qty(qty) {
		cout << "Bulk_quote constructor is running" << endl;
	}
	Bulk_quote(const Bulk_quote &bq): Disc_quote(bq), min_qty(bq.min_qty) {
		cout << "Bulk_quote copy constructor is runing" << endl;
		this->debug();
	}
	Bulk_quote(Bulk_quote &&bq) noexcept: Disc_quote(std::move(bq)), min_qty(bq.min_qty) {}
	Bulk_quote(const Quote &q) : Disc_quote(q) {
		cout << "Bulk_quote another copy constructor is running" << endl;
		this->debug();
	}
	void debug() {
		Disc_quote::debug();
		cout << "min_qty = " << min_qty << endl;
	}
	double net_price(size_t n) const override {
		if (n >= min_qty)
			return n * (1 - discount) * price;
		else
			return n * price;
	}
	virtual Bulk_quote *clone() const & { return new Bulk_quote(*this); }
	virtual Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }
};

double print_total(ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

class Basket {
	static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs) {
		return lhs->isbn() < rhs->isbn();
	}
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
public:
	void add_item(const shared_ptr<Quote> &sale) { items.insert(sale); }
	void add_item(const Quote &sale) { items.insert(shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote &&sale) { items.insert(shared_ptr<Quote>(std::move(sale).clone())); }
	double total_receipt(ostream &os) const {
		double sum = 0.0;
		for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
			sum += print_total(os, **iter, items.count(*iter));
		os << "Total Sale: " << sum << endl;
		return sum;
	}
};

#endif