#include <iostream>
#include <assert.h>
#include <istream>
#include <sstream>

/*
 Дан массив целых чисел А[0..n-1]. Известно, что
 на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).
 */

int run(std::istream& input, std::ostream& output);

int binary_search(int* array, int l, int r) {
    int left = l;
    int right = r-1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (array[mid] > array[mid+1]) {
            return array[mid+1];
        } else if (array[mid] < array[mid+1]) {
            left = mid + 1;
        }
    }
    return array[left];
}

int search(int* array, int size) {
    if (size == 1) return array[0];
    
    
    int i = 1;
    
    while(i < (size - 1) && array[i-1] < array[i]) {
        i *= 2;
    }
    
    int num = binary_search(array, i/2, i > (size) ? (size): i);
    return num;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "1 2 -1" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "-1\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "5" << std::endl;
        sstr_input << "1 -100 -101 -102 -103" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "-100\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "28" << std::endl;
        sstr_input << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 -12 -13" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "-1\n");
    }
    
    {
        std::stringstream sstr_input;
        sstr_input << "1" << std::endl;
        sstr_input << "10" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "10\n");
    }
    
    {
        std::stringstream sstr_input;
        sstr_input << "2" << std::endl;
        sstr_input << "1 2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "2\n");
    }
    
    {
        std::stringstream sstr_input;
        sstr_input << "2" << std::endl;
        sstr_input << "1 -1" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "-1\n");
    }
    
    {
        std::stringstream sstr_input;
        sstr_input << "2" << std::endl;
        sstr_input << "-1 -2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "-2\n");
    }
}

int run(std::istream& input, std::ostream& output) {
    int size;
    input >> size;
    
    assert(size > 0);
    
    int* array = new int[size];
    
    for (int i = 0; i < size; i++) {
        int num;
        input >> num;
        array[i] = num;
    }
    int searchValue = search(array, size);
    
    delete [] array;
    
    output << searchValue << std::endl;
    return 0;
}

int main(int argc, const char * argv[]) {
    
    //testLogic();
    //std::cout << "OK" << std::endl;
    
    return run(std::cin, std::cout);
}
