#pragma once

#include <string>
#include <memory>
#include <initializer_list>
using namespace std;

class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const StrVec &);
	StrVec(initializer_list<string>);
	StrVec &operator=(const StrVec &);
	~StrVec();
	void push_back(const string &);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string *begin() const { return elements; }
	string *end() const { return first_free; }
	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const string &);
private:
	allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	pair<string *, string *> alloc_n_copy(const string *, const string *);
	void free();
	void reallocate(size_t);
	void reallocate();
	string *elements;
	string *first_free;
	string *cap;
};