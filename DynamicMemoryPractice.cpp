#include <cstring>
#include "StrBlob.h"

void dynamic_array_practice() {
	const char *c1 = "Hello ";
	const char *c2 = "World!";
	size_t total_len = strlen(c1) + strlen(c2) + 1;
	char *r = new char[total_len];
	strcpy_s(r, strlen(c1) + 1, c1);
	strcat_s(r, total_len, c2);
	cout << r << endl;
	delete[]r;

	const string s1 = "hello ";
	const string s2 = "world!";
	size_t total_len2 = s1.size() + s2.size() + 1;
	char *r2 = new char[total_len2];
	strcpy_s(r2, total_len2, (s1 + s2).c_str());
	cout << r2 << endl;
	delete[]r2;
}

void allocator_practice() {
	string s_arr[2] = { "Hello", "World" };
	allocator<string> alloc;
	auto const p = alloc.allocate(10);
	auto q = p;
	alloc.construct(q++);
	alloc.construct(q++, "hi");
	alloc.construct(q++, 3, '6');
	//q = uninitialized_copy(begin(s_arr), end(s_arr), q);  //the parameter may be unsafe
	q = uninitialized_fill_n(q, 3, "!");
	size_t sz = q - p;
	for (size_t i = 0; i < sz; ++i)
		cout << p[i] << " ";
	cout << endl;
	while (q != p)
		alloc.destroy(--q);
	alloc.deallocate(p, 10);
}

void dynamic_memory_practice() {
	StrBlob sb = { "a", "b", "c" };
	sb.pop_back();
	sb.print(cout);

	dynamic_array_practice();

	allocator_practice();
}