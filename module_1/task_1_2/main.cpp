#include <iostream>
#include <assert.h>
#include <istream>
#include <sstream>
#include <cmath>

/*
   Вычислить  площадь  выпуклого  n-угольника,  заданного
   координатами своих вершин. Вначале вводится количество
   вершин, затем последовательно целочисленные координаты
   всех  вершин  в  порядке обхода против часовой стрелки
*/

struct Point {
    double x;
    double y;
};

int run(std::istream& input, std::ostream& output);

double calculateAreaTrapezoid(Point point1, Point point2) {
    assert(point1.x != point2.x || point1.y != point2.y);
    return (0.5) * (point1.y + point2.y) * (point2.x - point1.x);
}

double countAreaByPoints(Point* points, int size) {
    double sum = 0;
    
    if (size == 1) return 0;
    
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            sum += calculateAreaTrapezoid(points[i], points[0]);
        } else {
            sum += calculateAreaTrapezoid(points[i], points[i+1]);
        }
    }
    
    return abs(sum);
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "0 1  1 0  2 2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1.5\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "0 1  1 0  2 2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1.5\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "8" << std::endl;
        sstr_input << "-0.5 1  -1 0.5  -1 -0.5  -0.5 -1  0.5 -1  1 -0.5  1 0.5  0.5 1" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "3.5\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "-99 0  99 0  9999 0.5" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "49.5\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "4" << std::endl;
        sstr_input << "-0.02 -0.01  -0.02 -0.02  -0.01 -0.02  -0.1 -0.01" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "0.00035\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "-99 -99  -98 -99  -98.5 -98" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "0.5\n");
    }
}

int run(std::istream& input, std::ostream& output) {
    int size;
    input >> size;
    
    assert(size > 2 && size < 1000);
    
    Point* array = new Point[size];
    
    for (int i = 0; i < size; i++) {
        double x, y;
        input >> x >> y;
        assert(x < 10000 && y < 10000);
        array[i] = {x, y};
    }
    
    double res = countAreaByPoints(array, size);
    output << res << std::endl;
    delete[] array;
    
    return 0;
}

int main(int argc, const char * argv[]) {
    testLogic();
    std::cout << "OK" << std::endl;
    return run(std::cin, std::cout);
}

