#include <iostream>

template <typename T>
struct node {
    T arr[5];
    node<T>* next;
    int topN = 1;
    node(T v, node<T>* n = 0) {
        arr[0] = v;
        next = n;
    }
    bool full() {
        return (topN > 4);
    }
    bool empty() {
        return (topN < 1);
    }
};

template <class T>
struct Pila {
    node<T>* top = 0;
    void push(T v) {
        if (top) {
            if (top->full()) {
                top = new node<T>(v, top);
            }
            else {
                top->arr[top->topN] = v;
                top->topN++;
            }
        }
        else {
            top = new node<T>(v);
        }
    }

    T pop() {
        T tmp = 0;
        if (top) {
            if (top->empty()) {
                node<T>* aux = top;
                top = top->next;
                delete aux;
            }
            top->topN--;
            tmp = top->arr[top->topN];
        }
        return tmp;
    }

    void popAll() {
        std::cout << "TOP ->";
        while (top) {            
            std::cout << " "<< pop() << " -";  
            if (top->empty()) {
                std::cout << "> \n";
                top = top->next;
            }          
        }
        std::cout << " NULL\n";
    }

    void print() {
        std::cout << "TOP ->";
        node<T>* aux=top;
        while (aux) {
            for(int i=aux->topN-1;i>=0;i--){
                std::cout << " "<< aux->arr[i] << " -";
            }
            std::cout << "> \n";
            aux = aux->next;        
        }
        std::cout << " NULL\n";
    }
};

int main() {
    Pila<int> p1;
    //std::cout << "\n-------------------\n";
     for (int i=0;i<23;i++){
         p1.push(i);
     }
    p1.popAll();
    p1.print();
    p1.push(7);
    p1.print();
    p1.pop();
    p1.print();
}