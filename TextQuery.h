#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
using namespace std;

using line_no = vector<string>::size_type;

class QueryResult;
class TextQuery {
public:
	TextQuery(ifstream &);
	QueryResult query(const string &) const;
private:
	shared_ptr<vector<string>> text;
	map<string, shared_ptr<set<line_no>>> word_map;
};

class QueryResult {
	friend ostream &print(ostream &, const QueryResult &);
public:
	QueryResult(const string &w, shared_ptr<set<line_no>> l, shared_ptr<vector<string>> t):
		word(w), lines(l), text(t) {}
private:
	string word;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> text;
};