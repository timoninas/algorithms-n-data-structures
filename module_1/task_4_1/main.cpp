#include <iostream>
#include <assert.h>

template <class T>
class LilArray {
public:
    LilArray(): buf(nullptr), currentSize(0), maxSize(4) { buf = new T[maxSize]; }
    LilArray(T* array, int size);
    //~LilArray() { delete [] buf; }
    
    //    T& operator=(const T& val);
    //    T& operator=(T&& val);
    
    int count() const { return currentSize; }
    
    void swipe(const int &index1, const int &index2);
    const T& at(const int &index1);
    
    void print();
    bool is_empty() { return currentSize == 0; }
    void push_back(T val);
    void pop();
    const T& first();
    const T& last();
    
private:
    T* buf;
    int currentSize;
    int maxSize;
    
    bool is_full() { return currentSize == maxSize; }
    void grow();
};

template <typename T>
void LilArray<T>::swipe(const int &index1, const int &index2) {
    assert(index1 >= 0);
    assert(index2 >= 0);
    assert(index1 <= currentSize);
    assert(index2 <= currentSize);
    T tmp = buf[index1];
    buf[index1] = buf[index2];
    buf[index2] = tmp;
}

template <typename T>
const T& LilArray<T>::at(const int &index1) {
    assert(index1 >= 0);
    assert(index1 <= currentSize);
    return buf[index1];
}

template <typename T>
const T& LilArray<T>::first() {
    assert(!is_empty());
    return buf[0];
}

template <typename T>
const T& LilArray<T>::last() {
    assert(!is_empty());
    return buf[currentSize - 1];
}

template <typename T>
void LilArray<T>::pop() {
    if (currentSize > 0) {
        currentSize--;
    }
}

template <typename T>
LilArray<T>::LilArray(T* array, int size) {
    currentSize = 0;
    maxSize = 4;
    while(maxSize < size) {
        maxSize *= 2;
    }
    
    buf = new T[maxSize];
    
    for (int i = 0; i < size; i++) {
        buf[currentSize++] = array[i];
    }
}

template <typename T>
void LilArray<T>::print() {
    if (!is_empty()) {
        std::cout << "LilArray" << std::endl;
        std::cout << "bufferSize: " << maxSize << std::endl;
        std::cout << "currentSize: " << currentSize << std::endl;
        std::cout << "first: " << first() << std::endl;
        std::cout << "last: " << last() << std::endl;
        for (int i = 0; i < currentSize; i++) {
            std::cout << buf[i] << " ";
            if (i == currentSize - 1) {
                std::cout << std::endl << std::endl;
            }
        }
    } else {
        std::cout << "LilArray" << std::endl;
        std::cout << "Is Empty: " << std::endl << std::endl;
    }
}

template <typename T>
void LilArray<T>::push_back(T val) {
    if (is_full()) {
        grow();
    }
    
    buf[currentSize++] = val;
}

template <typename T>
void LilArray<T>::grow() {
    T* tmp_arr = new T[maxSize * 2];
    
    for (int i = 0; i < currentSize; i++) {
        tmp_arr[i] = buf[i];
    }
    
    delete [] buf;
    
    maxSize *= 2;
    buf = tmp_arr;
}

template <class T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template <class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(Comparator comp = Comparator());
    Heap(T* arr, int arr_size, Comparator comp = Comparator());
    
    ~Heap() { delete buf; }
    
    const T& top() const { return buf->first(); }
    void extract_top();
    
    void pop();
    void push(const T&);
    void push(T&&);
    
    
    bool is_empty() const { return buf->is_empty(); }
    int count() const { return buf->count(); }
    
private:
    LilArray<T>* buf;
    Comparator comp;
    
    void sift_up(int i);
    void sift_down(int i);
    void heapify();
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(T* arr, int arr_size, Comparator comp) {
    this->comp = comp;
    buf = new LilArray<T>(arr, arr_size);
    heapify();
}

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(Comparator comp) {
    this->comp = comp;
    buf = new LilArray<T>();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_down(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int curSize = count();
    int largest = i;
    
    if (left < curSize && buf->at(left) > buf->at(i)) {
        largest = left;
    }
    if (right < curSize && buf->at(right) > buf->at(largest)) {
        largest = right;
    }
    
    if (i != largest) {
        buf->swipe(i, largest);
        sift_down(largest);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::sift_up(int i) {
    while(i > 0) {
        int parent = (i - 1) / 2;
        if (buf->at(i) <= buf->at(parent))
            return;
        buf->swipe(i, parent);
        i = parent;
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify() {
    int sizee = count();
    for (int i = sizee / 2 - 1; i >= 0; i--) {
        sift_down(i);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& val) {
    buf->push_back(val);
    int size = count();
    sift_up(size - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(T&& val) {
    buf->push_back(val);
    int size = count();
    sift_up(size - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::extract_top() {
    assert(!is_empty());
    
    T last = buf->last();
    int last_index = count()-1;
    buf->swipe(0, last_index);
    buf->pop();
    sift_down(0);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
    assert(!is_empty());
    
    buf->pop();
}

int run(std::istream& input, std::ostream& output) {
    int size;
    input >> size;
    
    assert(size > 0);
    
    Heap<int> * heap = new Heap<int>();
    
    for (int i = 0; i < size; i++) {
        int num;
        input >> num;
        heap->push(num);
    }
    
    int weight;
    input >> weight;
    
    int *tmp_arr = new int[size];
    int current_size = 0;
    
    assert(heap->top() <= weight);
    
    int iterations = 0;
    
    while (!heap->is_empty()) {
        int tmp_weight = weight;
        current_size = 0;
        
        while(!heap->is_empty() && heap->top() <= tmp_weight) {
            int popped = heap->top();
            heap->extract_top();
            tmp_arr[current_size++] = popped;
            tmp_weight -= popped;
        }
        
        for (int i = 0; i < current_size; i++) {
            if (tmp_arr[i] != 1) {
                heap->push(tmp_arr[i] / 2);
            }
        }
        
        iterations++;
    }
    
    free(tmp_arr);
    delete heap;
    
    output << iterations << "\n";
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    return run(std::cin, std::cout);;
}
