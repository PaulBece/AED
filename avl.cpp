#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
#define y node<T>
using namespace std;

template <class T>
struct node {
	T valor;
	y* nodes[2] = {0,0};
	int altura;
	node(T v, int h=1){
		valor = v;
		altura = h;
	}
};

template <class T>
struct duo {
	T valor;
	int estado = 0;
};

template <class T>
struct AVL {
	y* root = 0;
	bool find(T v, y** &p, stack<y**>& s);
	bool insert(T v);
	void print(y* r);
	void porAmplitud(y* r);
};

template <typename T>
bool AVL<T>::find(T v, y**& p, stack<y**> &s) {
	p = &root;
	while (*p) {
		s.push(p);
		if (v < (*p)->valor)
			p = &((*p)->nodes[0]);
		else if ((*p)->valor == v)
			return 1;
		else
			p = &((*p)->nodes[1]);		
	}
	return 0;
}

template <typename T>
bool AVL<T>::insert(T v) {
	y** p;
	int c;
	int ant = 0;
	stack<y**> s;
	if (find(v, p, s)) return 0;
	*p = new y(v);
	while (!s.empty()) {
		if ((*s.top())->nodes[0]) {
			if ((*s.top())->nodes[1]) {
				(*s.top())->altura = max((*s.top())->nodes[0]->altura, (*s.top())->nodes[0]->altura) + 1;
				c = (*s.top())->nodes[1]->altura - (*s.top())->nodes[0]->altura;
			}
			else {
				(*s.top())->altura = (*s.top())->nodes[0]->altura + 1;
				c = -(*s.top())->nodes[0]->altura;				
			}
		}
		else {
			if ((*s.top())->nodes[1]) {
				(*s.top())->altura = (*s.top())->nodes[1]->altura + 1;
				c = (*s.top())->nodes[1]->altura;				
			}
			else
				c = 0;
		}
		
		switch (c)
		{
		case 2:
			if (ant == 1)
				rightline(*s.top());
			else
				righttriangle(*s.top());
			return 1;
		case -2:
			if (ant == -1)
				leftline(*s.top());
			else
				lefttriangle(*s.top());
			return 1;
		default:
			break;
		}
		ant = c;
		s.pop();
	}
	return 1;
}

template <class T>
void AVL<T>::porAmplitud(y* r) {
	queue<duo<y*>> cola;
	duo<y*> d1;
	d1.valor = r;
	d1.estado = 0;
	cola.push(d1);
	while (d1.valor) {
		duo<y*> tmp;
		tmp.valor = d1.valor->nodes[0];
		tmp.estado = d1.estado + 1;
		if (d1.valor->nodes[0]) {
			tmp.valor = d1.valor->nodes[0];
			cola.push(tmp);
		}
		if (d1.valor->nodes[1]) {
			tmp.valor = d1.valor->nodes[1];
			cola.push(tmp);
		}
		cola.pop();
		cout << d1.valor->valor << "-" << d1.estado << " ";
		if (cola.empty())
			d1.valor = 0;
		else
			d1 = cola.front();
	}
	cout << endl;
}

template <class T>
void AVL<T>::print(y* r) {
	if (!r) return;
	print(r->nodes[0]);
	cout << r->valor << "-" << r->altura << " ";
	print(r->nodes[1]);
}

template <class T>
void leftline(y* &r) {
	y* tmp1 = r;//tmp1->C
	r = r->nodes[0];//r->B
	y* tmp2 = r->nodes[1];//tmp2->Br
	r->nodes[1] = tmp1;//Br->C
	tmp1->nodes[0] = tmp2;//Cl->Br
}

template <class T>
void lefttriangle(y* &r) {
	y* tmp1 = r;//tmp1->C
	r = r->nodes[0]->nodes[1];//r->B
	y* tmp2 = r->nodes[0];//tmp2->Bl
	r->nodes[0] = tmp1->nodes[0];//Bl->A
	r->nodes[0]->nodes[1] = tmp2;//Ar->Bl
	tmp1->nodes[0] = r->nodes[1];//Cl->Br
	r->nodes[1] = tmp1;//Br->C
}

template <class T>
void rightline(y*& r) {
	y* tmp1 = r;//tmp1->A
	r = r->nodes[1];//r->B
	y* tmp2 = r->nodes[0];//tmp2->Bl
	r->nodes[0] = tmp1;//Bl->A
	tmp1->nodes[1] = tmp2;//Ar->Bl
}

template <class T>
void righttriangle(y*& r) {
	y* tmp1 = r;//tmp1->A
	r = r->nodes[1]->nodes[0];//r->B
	y* tmp2 = r->nodes[1];//tmp2->Br
	r->nodes[1] = tmp1->nodes[1];//Br->C
	r->nodes[1]->nodes[0] = tmp2;//Cl->Br
	tmp1->nodes[1] = r->nodes[0];//Ar->Bl
	r->nodes[0] = tmp1;//Bl->A
}

int main() {
	AVL<int> t1;
	t1.insert(10);
	t1.insert(5);
	t1.insert(15);
	t1.insert(3);
	t1.insert(8);
	t1.insert(13);
	t1.insert(18);
	t1.insert(2);
	t1.insert(4);
	t1.insert(7);
	t1.insert(9);
	t1.insert(12);
	t1.insert(14);
	t1.insert(17);
	t1.insert(19);
	t1.insert(1);
	t1.insert(0);
	t1.insert(21);
	t1.insert(20);
	t1.porAmplitud(t1.root);

	return 0;
}