#include <iostream>

template <class T>
class Cdeque {
    T* map[11];
    T** FRONT;
    T** BACK;
    T* front;
    T* back;
    T error = 0;

public:
    Cdeque<T>() {
        map[5] = new T[10];
        BACK = map + 5;
        FRONT = map + 5;
        front = (*FRONT) + 4;
        back = (*BACK) + 5;
    }
    ~Cdeque<T>() {
        while (FRONT <= BACK)
            delete[] *FRONT++;
    }
    void push_back(T v);
    void push_front(T v);
    T pop_back();
    T pop_front();
    int size();
    T& operator [] (int i);
};

template <class T>
void Cdeque<T>::push_back(T v) {
    if (back <= *(BACK)+9) {
        *(back++) = v;
    }
    else {
        if (BACK < map + 10) {
            *(++BACK) = new T[10];
            back = *BACK;
            *back++ = v;
        }
    }
}

template <class T>
void Cdeque<T>::push_front(T v) {
    if (front >= *FRONT) {
        *(front--) = v;
    }
    else {
        if (FRONT > map) {
            *(--FRONT) = new T[10];
            front = *(FRONT)+9;
            *front-- = v;
        }
    }
}

template <class T>
T Cdeque<T>::pop_back() {
    T tmp = error;
    if (BACK != FRONT || back > front + 1) {
        if (back != *BACK)
            tmp = *--back;
        else {
            delete[] * BACK--;
            back = *(BACK)+9;
            tmp = *back;
        }
    }
    return tmp;
}

template <class T>
T Cdeque<T>::pop_front() {
    T tmp = error;
    if (BACK != FRONT || back > front + 1) {
        if (front != *(FRONT)+9)
            tmp = *++front;
        else {
            delete[] * FRONT++;
            front = *FRONT;
            tmp = *front;
        }
    }
    return tmp;
}

template <class T>
int Cdeque<T>::size() {
    int tmp;
    int aux = BACK - FRONT;
    if (aux == 0)
        tmp = back - front - 1;
    else {
        tmp = (aux - 1) * 10;
        int a = ((*FRONT) + 9) - front;
        int b = back - (*BACK);
        tmp += ((*FRONT)+9) - front + back - (*BACK);
    }
    return tmp;
}

template <class T>
T& Cdeque<T>::operator [] (int i) {
    int s = size();
    if (s > i) {
        int aux1, aux2;
        aux1 = i / 10;
        aux2 = i % 10 + front - *FRONT + 1;
        if (aux2 < 10)
            return *(*(FRONT + aux1) + aux2);
        else {
            return *(*(FRONT + aux1 + 1) + aux2 - 10);
        }
    }
    return error;
}

int main() {
    Cdeque<int> d1;
    for (int i = 1; i < 13; i++) {
        d1.push_back(i);
        d1.push_front(i);
    }
    int s = d1.size();

    for (int i = 0; i < s; i++)
        std::cout << d1[i] << " ";
    std::cout << "\n";

    for (int i = 0; i < s / 3; i++) {
        std::cout << d1.pop_front() << " ";
        std::cout << d1.pop_back() << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < s; i++)
        std::cout << d1[i] << " ";
    d1[7] = 88;
    std::cout << "\n";

    for (int i = 0; i < s; i++)
        std::cout << d1[i] << " ";

    return 0;
}