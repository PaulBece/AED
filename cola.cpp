#include <iostream>

template<typename T>
struct nodo {
    T valor;
    nodo<T>* next;
    nodo(T v, nodo<T>* n=0) {
        valor = v;
        next = n;
    }
};

template<class T>
struct cola{
    nodo<T>* head = 0;
    nodo<T>* tail = 0;
    void push(T v);
    T pop();
    bool vacio();
    void popAll();
};

template<class T>
bool cola<T>::vacio() {
    return !head;
}

template<class T>
void cola<T>::push(T v) {
    if (vacio()) {
        head = new nodo<T>(v);
        tail = head;
    }
    else {
        tail->next= new nodo<T>(v, tail);
        tail = tail->next;
    }
}

template<class T>
T cola<T>::pop() {
    T tmp = 0;
    if (!vacio()) {
        tmp = head->valor;
        if (head == tail) {
            delete head;
            head = 0;
            tail = 0;
        }
        else {
            nodo<T>* aux = head;
            head = head -> next;
            delete aux;
        }
    }
    return tmp;
}

template<class T>
void cola<T>::popAll() {
    while (!vacio()) {
        std::cout << pop() << " ";
    }
    std::cout<<"\n";
}

int main()
{
    cola<int> C;
    for (int i = 0; i < 10; i++) {
        C.push(i);
    }
    C.popAll();
    C.push(15);
    C.push(9);
    C.push(6);
    C.push(20);
    C.popAll();

    return 0;
}