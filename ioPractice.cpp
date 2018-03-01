#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

istream &read_from_stream(istream &in) {
	int val;
	cout << "Type some integers:" << endl;
	while (in >> val, !in.eof()) {
		if (in.bad()) {
			throw runtime_error("wrong IO stream");
		}
		if (in.fail()) {
			cerr << "wrong data, try again:" << endl;
			in.clear();
			in.ignore(100, '\n');
			continue;
		}
		cout << val << endl;
	}
	in.clear();
	return in;
}

istream &write_to_file(istream &in) {
	string str;
	ofstream out("record.txt", ofstream::app);
	cout << "Type some words to record.txt:" << endl;
	while (getline(in, str), !in.eof()) {
		out << str << endl;
	}
	in.clear();
	return in;
}

ostream &print_to_stream(ostream &os, const string &s, char c) { return os << s << c; }

void stream_iterator_test() {
	cout << "istream_iterator for vector<int>:" << endl;
	istream_iterator<int> in_iter(cin), eof;
	vector<int> vi;
	//while (in_iter != eof) { vi.push_back(*in_iter++); }
	vi.assign(in_iter, eof);
	cin.clear();
	ostream_iterator<int> out_iter(cout, " ");
	//for (const auto &i : vi) { *out_iter++ = i; } //EQUAL TO: out_iter = i;
	copy(vi.begin(), vi.end(), out_iter);
	cout << endl;
	
	/*cout << "istream_iterator for vector<int>:" << endl;
	istream_iterator<int> in_iter2(cin), eof2;
	vector<int> vi2(in_iter2, eof2);
	for (const auto &i2 : vi2) { cout << i2 << " "; }
	cout << endl;
	cin.clear();*/
}

void io_practice() {
	//read_from_stream(cin);
	//write_to_file(cin);
	stream_iterator_test();

	cout << "Type some integers:" << endl;
	istream_iterator<int> in_iter(cin), eof;
	cout << "The sum is: " << accumulate(in_iter, eof, 0) << endl;
}