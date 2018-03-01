#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TextQuery.h"
using namespace std;

TextQuery::TextQuery(ifstream &input): text(new vector<string>) {
	string line;
	while (getline(input, line)) {
		text->push_back(line);
		size_t no = text->size() - 1;
		istringstream is(line);
		string word;
		while (is >> word) {
			auto &lines = word_map[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(no);
		}
	}
}

QueryResult TextQuery::query(const string &s) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = word_map.find(s);
	if (loc == word_map.end())
		return QueryResult(s, nodata, text);
	else
		return QueryResult(s, loc->second, text);
}

ostream &print(ostream &os, const QueryResult &qr) {
	os << qr.word << " occurs " << qr.lines->size() << " time(s)" << endl;
	for (auto no : *(qr.lines))
		os << "\t(line " << no + 1 << ") " << *(qr.text->begin() + no) << endl;
	return os;
}

void run_queries(const char* filename) {
	ifstream input(filename);
	TextQuery tq(input);
	while (true) {
		cout << "enter word to look for, or q to quit:" << endl;
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}