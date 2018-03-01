#pragma once

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <iostream>
using namespace std;

class StrBlobPtr;
class StrBlob {
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob(): data(make_shared<vector<string>>()) {}
	StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}
	inline size_type size() const { return data->size(); }
	inline bool empty() const { return data->empty(); }
	inline void push_back(const string &s) { data->push_back(s); }
	void pop_back();
	string &front();
	const string &front() const;
	string &back();
	const string &back() const;
	StrBlobPtr begin() const;
	StrBlobPtr end() const;
	ostream &print(ostream &os) const;
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

class StrBlobPtr {
	friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &sb, size_t sz = 0) : wptr(sb.data), curr(sz) {}
	StrBlobPtr(const StrBlob &sb, size_t sz = 0) : wptr(sb.data), curr(sz) {}
	string &deref() const;
	StrBlobPtr &incr();
private:
	shared_ptr<vector<string>> check(size_t i, const string &msg) const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

inline void StrBlob::check(size_type i, const string &msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}
inline void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
inline string &StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
inline const string &StrBlob::front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}
inline string &StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
inline const string &StrBlob::back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}
inline StrBlobPtr StrBlob::begin() const { return StrBlobPtr(*this); }
inline StrBlobPtr StrBlob::end() const { return StrBlobPtr(*this, data->size()); }
inline ostream &StrBlob::print(ostream &os) const {
	for (auto iter = data->cbegin(); iter != data->cend(); ++iter)
		os << *iter << " ";
	os << endl;
	return os;
}

inline shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
	auto p = wptr.lock();
	if (!p)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= p->size())
		throw out_of_range("msg");
	return p;
}
inline string &StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
inline StrBlobPtr &StrBlobPtr::incr() {
	auto p = check(curr, "dereference past end");
	++curr;
	return *this;
}

inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
	auto lp = lhs.wptr.lock(), rp = rhs.wptr.lock();
	if (lp == rp)
		return (!lp || lhs.curr == rhs.curr);
	else
		return false;
}
inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !eq(lhs, rhs); }