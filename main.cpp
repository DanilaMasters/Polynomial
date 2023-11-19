#include <iostream>
#include "Polynomial.h"
#include "Polynomial.cpp"
#include "test.cpp"

int main() {
    testAll();

    Polynomial p1({1, 2, 3, 4});
    Polynomial p2({2, 3, 1, 4});

    int val1[] = {1, 2, 3, 4};
    int val2[] = {1, 2, 3};

    Polynomial p3(3, val1);
    Polynomial p4(2, val2);

    Polynomial p5({1, 2, 3, 4, 5});
    Polynomial p6({2, 3, 1, 4});

    std::cout << "(" << p1 << ")" << " + " << "(" << p2 << ")" << " = " << addition(p1, p2) << std::endl;
    std::cout << "(" << p3 << ")" << " + " << "(" << p4 << ")" << " = " << p3 + p4 << std::endl;
    std::cout << "(" << p5 << ")" << " + " << "(" << p6 << ")" << " = " << p5 + p6 << std::endl;

    std::cout << "(" << p5 << ")" << " * " << "(" << p6 << ")" << " = " << p5 * p6 << std::endl;

    std::cout << "p1(5)= " << p1(5) << std::endl;
    std::cout << "p2(5)= " << p2(5) << std::endl;

    return 0;
}
