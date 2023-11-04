#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
#define y node<T>
using namespace std;

template <typename T>
struct node {
	T valor;
	y* left = 0;
	y* right = 0;
	y* up;
	bool red = 1;
	node(T v, y* u = 0) {
		valor = v;
		up = u;
	}
	T getFather() {
		if (!up) return 0;
		return up->valor;
	}
};

template <class T>
struct RBtree {
	y* root = 0;	
	bool insert(T v);
	bool remove(T v);
	void print();	
private:
	void inOrder(y* r);
	bool find(T v, y**& p, stack<y**>& s);
	void balance(stack<y**>& s);
	void changeColor(y* n);
	void redUncle(y** f, bool leftFather);
	void blackUncle(y** &f, bool leftChild, bool leftFather);
};

template <class T>
bool RBtree<T>::find(T v, y**& p, stack<y**>& s) {
	p = &root;
	while (*p) {
		s.push(p);
		if (v < (*p)->valor) {
			p = &((*p)->left);
		}
		else {
			if (v == (*p)->valor) {
				return 1;
			}
			p = &((*p)->right);
		}
	}
	return 0;
}

template <class T>
bool RBtree<T>::insert(T v) {
	y** p;
	stack<y**> s;
	if (find(v, p, s)) return 0;
	if (!s.empty()) {
		(*p) = new y(v, *s.top());
	}
	else {
		(*p) = new y(v);
		(*p)->red = 0;
	}
		
	balance(s);
	return 1;
}

template <class T>
void RBtree<T>::changeColor(y* n) {
	if (n->red)
		n->red = 0;
	else
		n->red = 1;
}

template <class T>
void RBtree<T>::redUncle(y** f, bool leftFather) {
	changeColor(*f);
	changeColor((*f)->up);
	if (leftFather)
		changeColor((*f)->up->right);
	else
		changeColor((*f)->up->left);
}

template <class T>
void RBtree<T>::blackUncle(y** &f, bool leftChild, bool leftFather) {
	if (leftChild && leftFather) {//lineleft(/)

		if ((*f)->up->up) {//tiene bisabuelo?
			if ((*f)->up->up->left == (*f)->up) {//el abuelo es hijo izquierdo
				(*f)->up->up->left = (*f);//r->B
				y* tmp1 = (*f)->right;//tmp1->Br
				(*f)->right = (*f)->up;//Br->C
				(*f)->up = (*f)->up->up;//Bu->r
				(*f)->right->up = *f;//Cu->B
				f = &((*f)->up->left);//f->r
				(*f)->right->left = tmp1;//Cl->Br
				if (tmp1) {//existe Br?
					tmp1->up = (*f)->right;//BRu->C
				}
			}
		}
	}

	else if (leftChild && !leftFather) {//righttriangle(>)
		cout << "1 0";

	}

	else if (!leftChild && leftFather) {//lefttriangle(<)
		cout << "0 1";

	}

	else {//lineright(\)
		cout << "0 0";

	}
}

template <class T>
void RBtree<T>::balance(stack<y**>& s) {
	while (!s.empty()) {
		if ((*s.top())->red) {
			if ((*s.top())->left) {
				if ((*s.top())->left->red) {
					if ((*s.top())->up->left == (*s.top())){
						if ((*s.top())->up->right && (*s.top())->up->right->red)
							redUncle(s.top(), 1);
						else
							blackUncle(s.top(), 1, 1);
					}
					else{
						if ((*s.top())->up->left && (*s.top())->up->left->red)
							redUncle(s.top(), 0);
						else
							blackUncle(s.top(), 1, 0);
					}
				}
			}
			if ((*s.top())->right) {
				if ((*s.top())->right->red) {
					if ((*s.top())->up->left == (*s.top())){
						if ((*s.top())->up->right->red)
							redUncle(s.top(), 1);
						else
							blackUncle(s.top(), 0, 1);
					}
					else{
						if ((*s.top())->up->left->red)
							redUncle(s.top(), 0);
						else
							blackUncle(s.top(), 0, 0);
					}
				}
			}
		}
		else
			return;
		s.pop();
	}
}



template <class T>
bool RBtree<T>::remove(T v) {

}

template <class T>
void RBtree<T>::print() {
	inOrder(root);
}

template <class T>
void RBtree<T>::inOrder(y* r) {
	if (!r) return;
	inOrder(r->left);
	cout << r->valor << "-" << r->getFather() << "  ";
	inOrder(r->right);
}

int main() {
	RBtree<int> t1;
	t1.insert(50);
	t1.insert(25);
	//t1.insert(75);
	t1.insert(13);
	//t1.insert(63);

	t1.print();

	return 0;
}