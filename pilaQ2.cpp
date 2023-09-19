#include <iostream>

template <typename T>
struct nodeQ {
    T arr[5];
    nodeQ<T>* next;
    nodeQ(T v, nodeQ<T>* n = 0) {
        *arr = v;
        next = n;
    }
};

template <class T>
struct pilaQ {
    nodeQ<T>* TOP = 0;
    T* top = 0;

    bool isFull() {
        return (TOP->arr + 4 == top);
    }

    bool isEmpty() {
        return (TOP->arr - 1 == top);
    }

    void push(T v) {
        if (!TOP || isFull()) {
            TOP = new nodeQ<T>(v, TOP);
            top = TOP->arr;
        }
        else {
            *(++top) = v;
        }
    }

    T pop() {
        T tmp = 0;
        if (TOP) {
            tmp = *(top--);
            if (isEmpty()) {
                nodeQ<T>* aux = TOP;
                TOP = TOP->next;
                delete aux;
                //if (TOP)
                    top = TOP->arr + 4;
            }
        }
        return tmp;
    }

    void print() {
        nodeQ<T>* AUX = TOP;
        T* aux = top;
        std::cout << "HEAD -> ";
        while (AUX) {
            for (; aux >= AUX->arr; aux--) {
                std::cout << *aux << " -";
            }
            std::cout << ">\n";
            AUX = AUX->next;
            //if(AUX)
                aux = AUX->arr + 4;
        }
        std::cout << "NULL\n";
    }
};

int main() {
    pilaQ<int> p1;
    for (int i = 0; i < 23; i++)
        p1.push(i);
    p1.print();

    while(p1.TOP){
        std::cout<<p1.pop()<<" ";
    }
    std::cout<<"\n";
    p1.print();

    return 0;
}