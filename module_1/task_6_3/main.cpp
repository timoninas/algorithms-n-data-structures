#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/*
 Реализуйте  стратегию  выбора  опорного  элемента
 “случайный элемент”. Функцию Partition реализуйте
 методом   прохода  двумя  итераторами  от  начала
 массива к концу.
 */

void print_arr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int partition(int *arr, int l, int r) {
    assert(r - 1 >= 0);
    srand(time(0));
    int pivot_idx = l + rand() % (r - l);
    int pivot = arr[pivot_idx];
    
    int i = l;
    int j = l;
    
    std::swap(arr[pivot_idx], arr[r-1]);
    
    while (true) {
        for (; arr[j] >= pivot && j < (r-1); j++);
        if (j >= (r-1) || i >= (r-1) ) break;
        if (i != j) {
            std::swap(arr[i], arr[j]);
        }
        i++;
        j++;
    }
    
    std::swap(arr[i], arr[j]);
    return i;
}

int kth_position(int *arr, const int &size, int k) {
    int l = 0;
    int r = size;
    
    while(l <= r) {
        int m = partition(arr, l, r);
        if (m == k) { break; }
        else if (m < k) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    
    return 0;
}

int run(std::istream& input, std::ostream& output) {
    int size;
    input >> size;
    assert(size > 0);
    
    int k;
    input >> k;
    assert(k >= 0 && k < size);
    
    int * array = new int[size];
    for (int i = 0; i < size; i++) {
        int num;
        input >> num;
        array[i] = num;
    }
    
    kth_position(array, size, k);
    
    output << array[k] << "\n";
    
    return 0;
}

int main(int argc, const char * argv[]) {
    return run(std::cin, std::cout);
}
