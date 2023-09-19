#include <iostream>

template <typename T>
struct node {
    T arr[5];
    node<T>* next;
    node(T v, node<T>* n = 0) {
        *arr = v;
        next = 0;
    }
};

template <class T>
struct cola {
    node<T>* HEAD = 0;
    node<T>* TAIL = 0;
    T* head = 0;
    T* tail = 0;

    bool isFull() {
        return tail == TAIL->arr + 4;
    }
    bool isEmpty() {
        return head == HEAD->arr + 5;
    }

    void push(T v) {
        if (TAIL) {
            if (isFull()) {
                TAIL->next = new node<T>(v);
                TAIL = TAIL->next;
                tail = TAIL->arr;
            }
            else {
                *(++tail) = v;
            }
        }
        else {
            HEAD = new node<T>(v);
            TAIL = HEAD;
            head = HEAD->arr;
            tail = head;
        }
    }

    T pop() {
        T tmp = 0;
        if (HEAD) {
            if (head == tail) {
                tmp = *head;
                head = 0;
                tail = 0;
                HEAD = 0;
                TAIL = 0;
            }
            else {
                tmp = *(head++);
                if (isEmpty()) {
                    node<T>* aux = HEAD;
                    HEAD = HEAD->next;
                    delete aux;
                    head = HEAD->arr;
                }
            }            
        }
        return tmp;
    }

    void print() {
        std::cout << "HEAD ->";
        node<T>* aux = HEAD;
        T* aux2 = head;
        while (aux) {
            if (aux == TAIL) {
                for (; aux2 <= tail; aux2++) {
                    std::cout << " " << *aux2 << " -";
                }
            }
            else {
                for (; aux2 != aux->arr + 5; aux2++) {
                    std::cout << " " << *aux2 << " -";
                }
            }
            std::cout << "> \n";
            aux = aux->next;
            aux2 = aux->arr;
        }
        std::cout << " NULL\n";
    }

};

int main()
{
    cola<int> c1;
    for (int i = 0; i < 22; i++) {
        c1.push(i);
    }
    c1.print();

    while (c1.HEAD) {
        std::cout << c1.pop() << " ";
    }
    std::cout<<"\n";

    c1.print();
    std::cout<<c1.pop();

    return 0;
}