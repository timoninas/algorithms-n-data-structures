#include <iostream>

template <class T>
T foo(T e) {
    return e;
}

template <class T>
class DEQ {
public:
    DEQ();
    ~DEQ();
    
    void push_front(T value);
    void push_back(T value);
    
    T pop_front();
    T pop_back();
    
    bool is_empty();
    
private:
    T* array;
    int buffer_size;
    int front, back;
    int size;
    
    void grow();
    bool is_full();
};

template <class T>
DEQ<T>::DEQ() {
    buffer_size = 0;
    array = nullptr;
    front = 0;
    back = 0;
    size = 0;
}

template <class T>
DEQ<T>::~DEQ() {
    delete [] array;
}

template <class T>
void DEQ<T>::grow() {
    if (buffer_size <= 0) {
        buffer_size = 1;
        array = new T[buffer_size];
        return;
    }
    
    T* new_array = new T[buffer_size * 2];
    
    int k = 0;
    int i = front;
    do {
        if (i == buffer_size) {
            i = 0;
        }
        
        new_array[k++] = array[i];
        i++;
    } while (k < size);
    
    front = 0;
    back = k;
    buffer_size *= 2;
    
    delete [] array;
    
    array = new_array;
}

template <class T>
bool DEQ<T>::is_full() {
    return size == buffer_size;
}

template <class T>
bool DEQ<T>::is_empty() {
    return size == 0;
}

template <class T>
void DEQ<T>::push_front(T value) {
    if (is_full()) {
        grow();
    }
    
    front--;
    
    if (front == -1) {
        front = buffer_size-1;
    }
    
    array[front] = value;
    size++;
}

template <class T>
void DEQ<T>::push_back(T value) {
    if (is_full()) {
        grow();
    }
    
    if (back == buffer_size) {
        back = 0;
    }
    
    array[back] = value;
    back++;
    size++;
}

template <class T>
T DEQ<T>::pop_front() {
    assert(!is_empty());
    
    size--;
    T val = array[front];
    front++;
    
    if (front == buffer_size) {
        front = 0;
    }
    
    return val;
}

template <class T>
T DEQ<T>::pop_back() {
    assert(!is_empty());
    
    size--;
    back--;
    
    if (back == 0) {
        back = buffer_size - 1;
    }
    
    return array[back];
}

int main(int argc, const char * argv[]) {
    
    DEQ<int> *que = new DEQ<int>();
    
    que->push_front(1);
    que->push_front(2);
    que->push_front(3);
    que->push_back(9);
    que->push_front(4);
    que->push_front(5);
    que->push_front(6);
    
    return 0;
}
