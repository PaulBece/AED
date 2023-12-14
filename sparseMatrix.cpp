#include <iostream>
#include <vector>

using namespace std;

template <class T, T null = 0>
struct sparseMatrix;

template <class T, T null>
struct CX;

template <class T>
struct node {
	T value;
	int row, col;
	node<T>* nextR, *nextC;
	node(T v, int r, int c, node<T>* nR, node<T>* nC) : value(v), row(r), col(c), nextR(nR), nextC(nC) {}
};

template <class T, T null>
struct sparseMatrix {
	vector<node<T>*> rows;
	vector<node<T>*> columns;
	sparseMatrix(int r, int c) {
		rows.resize(r);
		columns.resize(c);
	}
	bool findR(int row, int col, node<T>** &p) {
		p = &(columns[col-1]);
		while (*p) {
			if ((*p)->row < row) {
				p = &((*p)->nextR);
			}
			else if ((*p)->row == row) {
				return 1;
			}
			else {
				break;
			}
		}
		return 0;
	}
	bool findC(int row, int col, node<T>** &p) {
		p = &(rows[row-1]);
		while (*p) {
			if ((*p)->col < col) {
				p = &((*p)->nextC);
			}
			else if ((*p)->col == col) {
				return 1;
			}
			else {
				break;
			}
		}
		return 0;
	}
	void set(T v, int row, int col) {
		node<T>** r;
		if (findR(row, col, r)) {
			(*r)->value = v;
		}
		else {
			node<T>** c;
			findC(row, col, c);
			*r = new node<T>(v, row, col, *r, *c);
			*c = *r;
		}
	}
	T get(int row, int col) {
		node<T>** r;
		if (findR(row, col, r)) return (*r)->value;
		return null;
	}
	void remove(int row, int col) {
		node<T>** r;
		if (findR(row, col, r)) {
			node<T>** c;
			findC(row, col, c);
			node<T>* tmp = *r;
			*r = (*r)->nextR;
			*c = (*c)->nextC;
			delete tmp;
		}
	}

	CX<T, null> operator() (int row, int col) {
		return CX<T, null>(row, col, this);
	}

	void print() {
		for (int r = 1; r <= rows.size(); r++) {
			for (int c = 1; c <= columns.size(); c++) {
				cout << get(r, c) << " ";
			}
			cout << endl;
		}
	}
};

template <class T, T null>
struct CX {
	sparseMatrix<T, null>* sm;
	int row, col;
	CX(int r, int c, sparseMatrix<T, null>* m) : row(r), col(c), sm(m) {}
	void operator=(T v) {
		sm->set(v, row, col);
	}
	operator int() {
		return sm->get(row, col);
	}
};

int main() {
	sparseMatrix<int> sm1(2, 3);
	sm1.set(15, 2, 3);
	sm1.set(20, 1, 1);
	sm1.set(30, 2, 2);
	sm1.set(25, 2, 1);
	sm1(1, 3) = 50;
	int a = sm1(1, 2);
	sm1.remove(2, 2);
	sm1.print();
	cout << a;

	return 0;
}