#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
using namespace std::placeholders;

extern ostream &print_to_stream(ostream &, const string &, char);

void sum(int a) {
	auto add = [a](int b) { return a + b; };
	cout << add(1) << endl;
}

auto isShorter = [](const string &s1, const string &s2) { return s1.size() < s2.size(); };

void elimDups(vector<string> &words) {
	sort(words.begin(), words.end());
	auto iter = unique(words.begin(), words.end());
	words.erase(iter, words.end());
}
void biggies(vector<string> &words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(), isShorter);

	auto iter = find_if(words.begin(), words.end(),
		[sz](const string &s) { return s.size() >= sz; });
	auto count = words.end() - iter;
	cout << count << " word(s) " << " of length " << sz << " or longer: ";
	for_each(iter, words.end(),
		[](const string &s) { cout << s << " "; });
	cout << endl;

	auto iter2 = partition(words.begin(), words.end(),
		[sz](const string &s) { return s.size() < sz; });
	auto count2 = words.end() - iter2;
	cout << count2 << " word(s) " << " of length " << sz << " or longer:" << endl;
	for_each(iter2, words.end(),
		[](const string &s) { cout << s << " "; });
	cout << endl;
}

void lambda_practice() {
	auto s = [](int a, int b) -> int { return a + b; };
	cout << s(1, 1) << endl;
	sum(1);

	vector<string> words{"fox", "jumps", "over", "quick", "red", "slow", "the", "turtle"};
	cout << "There are " << words.size() << " words: ";
	for (const auto &w : words) { cout << w << " "; }
	cout << endl;
	sort(words.begin(), words.end(), bind(isShorter, _2, _1));
	cout << "The descending order of the length of words: ";
	for_each(words.begin(), words.end(), bind(print_to_stream, ref(cout), _1, ' '));
	cout << endl << "Among them," << endl;
	biggies(words, 5);

	int i = 5;
	auto f = [i]() mutable -> bool { if (i > 0) { --i; return false; } else return true; };
	for (int j = 0; j < 6; ++j)
		cout << f() << " ";
	cout << endl;
}