#include <iostream>
#include <queue>
#define y node<T>
using namespace std;

template <class T>
struct duo {
	T valor;
	int estado = 0;
};

template <class T>
struct node {
	T valor;
	y* left;
	y* right;
	node(T v, y* l=0, y* r=0) {
		valor = v;
		left = l;
		right = r;
	}
};

template <typename T>
class tree {
	bool c = 1;
public:
	y* root=0;
	bool find(T v, y** &p);
	bool insert(T v);
	bool remove(T v);
	void inOrder(y* r);
	void inOrderRev(y* r);
	void preOrden(y* r);
	void posOrden(y* r);
	void porAmplitud(y* r);
	void print(int arg = 0);
};

template <class T>
bool tree<T>::find(T v, y** &p) {
	p = &root;
	while (*p) {
		if (v < (*p)->valor) {
			p = &(*p)->left;
		}
		else {
			if (v == (*p)->valor)
				return 1;
			p = &(*p)->right;
		}
	}
	return 0;
}

template <class T>
bool tree<T>::insert(T v) {
	y** p;
	if (find(v, p)) {
		return 0;
	}
	else {
		*p = new y(v);
	}
	return 1;
}

template <class T>
bool tree<T>::remove(T v) {
	y** p;
	if (find(v, p)) {
		if ((*p)->left && (*p)->right) {
			if (c) {
				y** q = &(*p)->left;
				while ((*q)->right) {
					q = &(*q)->right;
				}
				(*p)->valor = (*q)->valor;
				p = q;
				c = 0;
			}
			else {
				y** q = &(*p)->right;
				while ((*q)->left) {
					q = &(*q)->left;
				}
				(*p)->valor = (*q)->valor;
				p = q;
				c = 1;
			}
		}
		if ((*p)->left) {
			y* tmp = (*p);
			*p = (*p)->left;
			delete tmp;
		}
		else {
			y* tmp = (*p);
			*p = (*p)->right;
			delete tmp;
		}
		return 1;
	}
	return 0;
}

template <class T>
void tree<T>::inOrder(y* r) {
	if (r) {
		inOrder(r->left);
		cout << r->valor << " ";
		inOrder(r->right);
	}
}

template <class T>
void tree<T>::preOrden(y* r) {
	if (r) {
		cout << r->valor << " ";
		preOrden(r->left);
		preOrden(r->right);
	}
}

template <class T>
void tree<T>::posOrden(y* r) {
	if (r) {
		posOrden(r->left);
		posOrden(r->right);
		cout << r->valor << " ";
	}
}

template <class T>
void tree<T>::inOrderRev(y* r) {
	if (r) {
		inOrderRev(r->right);
		cout << r->valor << " ";
		inOrderRev(r->left);
	}
}

template <class T>
void tree<T>::porAmplitud(y* r) {
	queue<duo<y*>> cola;
	duo<y*> d1;
	d1.valor = r;
	d1.estado = 0;
	cola.push(d1);
	while (d1.valor) {
		duo<y*> tmp;
		tmp.valor = d1.valor->left;
		tmp.estado=d1.estado+1;
		if (d1.valor->left) {
			tmp.valor = d1.valor->left;
			cola.push(tmp);
		}
		if (d1.valor->right) {
			tmp.valor = d1.valor->right;
			cola.push(tmp);
		}
		cola.pop();
		cout << d1.valor->valor << "-"<< d1.estado<<" ";
		if (cola.empty())
			d1.valor = 0;
		else
			d1 = cola.front();
	}
	cout << endl;
}

template <class T>
void tree<T>::print(int arg) {
	switch (arg) {
	case 0:
		cout << "inOrder: ";
		inOrder(root);
		break;
	case 1:
		cout << "inOrderReverse: ";
		inOrderRev(root);
		break;
	case 2:
		cout << "preOrder: ";
		preOrden(root);
		break;
	case 3:
		cout << "posOrder: ";
		posOrden(root);
		break;
	}
	cout << endl;
}

int main() {
	tree<int> t1;
	t1.insert(20);
	t1.insert(10);
	t1.insert(30);
	t1.insert(5);
	t1.insert(8);
	t1.insert(25);
	t1.insert(35);
	//t1.remove(20);
	//t1.remove(10);
	t1.print();
	t1.print(1);
	t1.print(2);
	t1.print(3);
	t1.porAmplitud(t1.root);

	return 0;
}