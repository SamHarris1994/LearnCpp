#include "StrVec.h"
#include <algorithm>

pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) {
	auto data = alloc.allocate(e - b);
	return { data, uninitialized_copy(b, e, data) };
}
void StrVec::free() {
	if (elements) {
		for (auto p = first_free; p != elements; )  //reverse order
			alloc.destroy(--p);
		//for_each(elements, first_free, [](string &s) { alloc.destroy(s); });  //alloc cant be used
		alloc.deallocate(elements, cap - elements);
	}
}
void StrVec::reallocate(size_t newcapacity) {
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1;
	reallocate(newcapacity);
}
StrVec::StrVec(const StrVec &sv) {
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::StrVec(initializer_list<string> il) {
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec &StrVec::operator=(const StrVec &rhs) {
	free();
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}
StrVec::~StrVec() { free(); }
void StrVec::push_back(const string &s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void StrVec::reserve(size_t n) { if (n > capacity()) reallocate(n); }
void StrVec::resize(size_t n) {
	if (n > size()) {
		while (size() < n)
			push_back("");
	}
	else if (n < size()) {
		while (size() > n)
			alloc.destroy(--first_free);
	}
}
void StrVec::resize(size_t n, const string &s) {
	if (n > size())
		while (n > size())
			push_back(s);
}