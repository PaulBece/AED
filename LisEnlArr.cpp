#include <iostream>
#define P (*p)

template <class T>
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T>
class node {
public:
	T arr[5];
	node<T>* next;
	node(T v, node<T>* n=0) {
		*arr = v;
		next = n;
	}
};

template <class T>
class List {
	node<T>* head = 0;
	int size = 0;
	bool find(T v, node<T>** &p, int& f);
public:
	~List() {
		while (head) {
			node<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	bool insert(T v);
	bool remove(T v);
	void print();
};

template <typename T>
bool List<T>::find(T v, node<T>** &p, int &f) {
	p = &head;
	int aux = size;
	f = 0;
	while P {
		if (aux >= 5) {
			if (v > P->arr[4]) {
				p = &P->next;
				aux -= 5;
				f += 5;
			}
			else {
				for (int i = 4; i >= 0; i--) {
					if (v >= P->arr[i]) {
						if (v == P->arr[i]) {
							f += i;
							return 1;
						}
						else {
							f += i + 1;
							return 0;
						}
					}						
				}
				return 0;
			}
		}
		else {
			for (int i = aux - 1; i >= 0; i--) {
				if (v >= P->arr[i]) {
					if (v == P->arr[i]) {
						f += i;
						return 1;
					}
					else {
						f += i + 1;
						return 0;
					}
				}
			}
			return 0;
		}
	}
	return 0;
}

template <typename T>
bool List<T>::insert(T v) {
	node<T>** p;
	int f;
	if (find(v, p, f))
		return 0;
	else {
		if P {
			node<T>** q = p;
			T tmp = (*q)->arr[f % 5];
			for (int i = f; i < size; i++) {
				if (i % 5 == 4) {
					q = &(*q)->next;
					if (!*q)
						*q = new node<T>(0);
				}
				swap<T>(tmp, (*q)->arr[(i + 1) % 5]);
			}
			P->arr[f % 5] = v; 
		}
		else
			P = new node<T>(v);
		size++;
		return 1;
	}
}

template <typename T>
bool List<T>::remove(T v) {
	node<T>** p;
	int f;
	if (find(v, p, f)) {
		node<T>** q = p;
		for (int i = f; i < size - 1; i++) {
			if (i % 5 == 4) {
				(*q)->arr[4] = (*q)->next->arr[0];
				q = &(*q)->next;
			}
			else
				(*q)->arr[i % 5] = (*q)->arr[(i % 5) + 1];
		}
		size--;
		if (size % 5 == 0) {
			delete (*q);
			*q = 0;
		}
		return 1;
	}
	else
		return 0;
}

template <class T>
void List<T>::print() {
	node<T>* aux = head;
	int c = 0;
	while (c<size) {
		std::cout<<aux->arr[c%5]<<" ";
		if (c % 5 == 4) {
			aux = aux->next;
			std::cout << "\n";
		}
		c++;
	}
}

int main() {
	List<int> l1;
	for (int i = 1; i < 43; i++)
		l1.insert(i);
	for (int i = 1; i < 43; i++)
		l1.remove(i);
	for (int i = 42; i > 0; i--)
		l1.insert(i);
	/*for (int i = 42; i > 0; i--)
		l1.remove(i);*/
	l1.print();

	return 0;
}