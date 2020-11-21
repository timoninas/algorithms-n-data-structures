#include <iostream>
#include <assert.h>
#include <istream>
#include <sstream>

/*
 Вариант 2
 
 */

int run(std::istream& input, std::ostream& output);

int binary_search(int* array, int l, int r, int num) {
    int left = l;
    int right = r;
    while (left < right) {
        int mid = (left + right) / 2;
        if (array[mid] == num) {
            return mid;
        }
        
        if (array[mid] < num) {
            left = mid + 1;
        } else {
            right = mid;
        }
     }
    if (left != 0) {
        return left;
    } else {
        return 0;
    }
}

int search(int* array, int size, int number) {
    int i = 1;
    
    while(i < (size - 1) && array[i] < number) {
        i *= 2;
    }
    
    int num = binary_search(array, i/2, i > (size) ? (size-1): i, number);
//    int num = binary_search(array, 0, size, number);
    return num;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "1 2 3" << std::endl;
        sstr_input << "4" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "2\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "4" << std::endl;
        sstr_input << "1 3 5 6" << std::endl;
        sstr_input << "5" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "2\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "4" << std::endl;
        sstr_input << "1 3 5 6" << std::endl;
        sstr_input << "2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n");
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
    
    int number;
    input >> number;
    
    int position = search(array, size, number);
    
    delete [] array;
    
    output << position << std::endl;
    return 0;
}

int main(int argc, const char * argv[]) {
//    testLogic();
//    std::cout << "OK" << std::endl;
//
    return run(std::cin, std::cout);
    
//    std::stringstream sstr_input;
//    sstr_input << "6" << std::endl;
//    sstr_input << "1 2 4 7 9 12" << std::endl;
//    sstr_input << "5" << std::endl;
//    return run(sstr_input, std::cout);
}
