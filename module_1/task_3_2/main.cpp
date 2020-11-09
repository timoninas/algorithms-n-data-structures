#include <iostream>
#include <assert.h>

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

// push front - 1 num
// pop front  - 2 [ret num] if num == ret -> YES
// push back  - 3 num
// pop back   - 4 [ret num] if num != ret -> NO

int run(std::istream& input, std::ostream& output) {
    DEQ<int> *que = new DEQ<int>();
    
    int num = 0;
    input >> num;
    
    for (int i = 0; i < num; i++) {
        int command = 0;
        int command_value = -1;
        int que_value = -1;
        input >> command >> command_value;
        
        switch (command) {
            case 1:
                que->push_front(command_value);
                break;
            case 2:
                if (!que->is_empty()) {
                    que_value = que->pop_front();
                } else if (que->is_empty()) {
                    que_value = -1;
                }
                
                if (command_value != que_value) {
                    output << "NO" << "\n";
                    return 0;
                }
                break;
            case 3:
                que->push_back(command_value);
                break;
            case 4:
                if (!que->is_empty()) {
                    que_value = que->pop_back();
                } else if (que->is_empty()) {
                    que_value = -1;
                }
                
                if (command_value != que_value) {
                    output << "NO" << "\n";
                    return 0;
                }
                break;
            default:
                output << "NO" << "\n";
                return 0;
        }
    }
    output << "YES" << "\n";
    return 0;
}

int main(int argc, const char * argv[]) {
    
    return run(std::cin, std::cout);
}
