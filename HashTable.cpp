#include <iostream>
#include<list>
#include<vector>

using namespace std;

template <class T>
struct listAdapter {
	list<T> p;
	void insert(T value) {
		p.push_front(value);
	}
	void remove(T value) {
		p.remove(value);
	}
};

struct fString {
	int operator()(string s) {
		int size = s.size();
		int res = 0;
		for (int i = 0; i < size; i++) {
			res += s[i];
		}
		return res;
	}
};

template <class T,class F, int z, class Container = listAdapter<T>>
struct hashTable {
	F f;
	vector<Container> ht;
	hashTable() {
		ht.resize(z);
	}
	void insert(T value) {
		int i = f(value) % z;
		ht[i].insert(value);
	}
	void remove(T value) {
		int i = f(value) % z;
		ht[i].remove(value);
	}
};


int main() {
	
	hashTable<string, fString, 17> ht1;

	ht1.insert("Ignacio");
	ht1.insert("Ignacio");
	ht1.remove("Ignacio");

	return 0;
}