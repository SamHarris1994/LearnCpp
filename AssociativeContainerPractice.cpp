#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stdexcept>
using namespace std;

void subscript_test() {
	map<string, vector<string>> families;
	families["ZHAO"].push_back("Da");
	families["ZHAO"].push_back("Er");
	families["QIAN"].push_back("Da");
	for (const auto &f : families) {
		cout << f.first << endl;
		for (const auto &n : f.second)
			cout << "\t" << n << endl;
	}
}

void word_count(const char* file) {
	ifstream in(file);
	if (!in) {
		cout << "Fail to open file!" << endl;
		exit(1);
	}
	map<string, size_t> words;
	//unordered_map<string, size_t> words;
	string word;
	while (in >> word)
		++words[word];
	cout << "In the file " << file << ":" << endl << endl;
	for (const auto &w : words)
		cout << w.first << " occurs " << w.second << " time(s)" << endl;
}

//map is also suitable
unordered_map<string, string> build_map(ifstream &map_file) {
	unordered_map<string, string> trans_map;
	string key, value;
	while (map_file >> key && getline(map_file, value)) {
		if (value.size() > 1)
			trans_map[key] = value.substr(1);  //jump the space
		else
			throw runtime_error("no rule for" + key);
	}
	return trans_map;
}
const string &transform(const string &word, const unordered_map<string, string> &trans_map) {
	auto it = trans_map.find(word);
	return (it == trans_map.end()) ? word : it->second;
}
void word_transform(ifstream &map_file, ifstream &input_file) {
	auto trans_map = build_map(map_file);
	cout << "Here is our transformation map:" << endl << endl;
	for (const auto &entry : trans_map)
		cout << "Key: " << entry.first << "\t\tValue: " << entry.second << endl;
	cout << endl << endl;
	cout << "The transformed text is:" << endl << endl;
	string line;
	while (getline(input_file, line)) {
		istringstream in(line);
		string word;
		bool firstword = true;
		while (in >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

void associative_container_practice() {
	subscript_test();
	cout << endl << endl;
	word_count("input.txt");
	cout << endl << endl;
	ifstream map_file("map.txt");
	ifstream input_file("input.txt");
	word_transform(map_file, input_file);
}