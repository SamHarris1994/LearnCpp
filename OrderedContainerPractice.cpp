#include <iostream>
#include <vector>
#include <string>
using namespace std;

void ordered_container_practice() {
	vector<int> vi;
	vi.reserve(100);
	cout << "capacity: " << vi.capacity() << ", size: " << vi.size() << endl;
	for (int i = 0; i < 40; ++i)
		vi.push_back(i);
	vi.resize(vi.size() + vi.size() / 2);
	cout << "capacity: " << vi.capacity() << ", size: " << vi.size() << endl;
	for (int i = 0; i < 20; ++i)
		vi.push_back(i);
	vi.resize(vi.size() + vi.size() / 2);
	cout << "capacity: " << vi.capacity() << ", size: " << vi.size() << endl;

	vector<char> vc = { 'H', 'e', 'l', 'l', 'o' };
	string s(vc.data(), vc.size());  //data() returns the address of the first element
	cout << s << endl;
}