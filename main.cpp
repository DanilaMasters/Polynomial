#include <iostream>
#include <string>
#include "Polynomial.h"

using namespace std;

template<typename T, typename U>
void print(const Polynomial<T>& p1, const Polynomial<U>& p2, string lhs="p1", string rhs="p2", char sep='\n') {
    cout << lhs << " = " << p1 << sep << rhs << " = " << p2 << endl;
    cout << endl;
}

template<typename T>
void print(const Polynomial<T>& p, string name="p") {
    cout << name << " = " << p << endl;
}

int main() 
{
    Polynomial<double> p1({1.1, 2.0, 3.5, 4.7});
    Polynomial<int> p2({2, 3, 1, 4});
    print(p1, p2);

    p1[0] = 0;
    p2[1] = 0;
    print(p1, p2);

    p1.operator[](0) = 111;
    p2.operator[](3) = 444;
    print(++p1, p2++);

    Polynomial p22{1, 2, 3};
    p1 = p22;
    print(p22, p1, "p22", "p1");

    int val1[] = {1, 2, 3, 4};
    int val2[] = {1, 2, 3};

    Polynomial p3(3, val1);
    Polynomial p4(2, val2);

    Polynomial p5({1.2, 2, 3, 4.3, 5});
    Polynomial p6({2, 3, 1, 4});

    std::cout << "(" << p3 << ")" << " + " << "(" << p4 << ")" << " = " << p3 + p4 << std::endl;
    std::cout << "(" << p5 << ")" << " + " << "(" << p6 << ")" << " = " << p5 + p6 << std::endl;

    std::cout << "(" << p5 << ")" << " * " << "(" << p6 << ")" << " = " << p5 * p6 << std::endl;

    std::cout << "p1(5)= " << p1(5) << std::endl;
    std::cout << "p2(5)= " << p2(5) << std::endl;
    
    std::cin >> p22;
    std::cout << "p22= " << p22 << std::endl;

    p22 += p6;
    std::cout << "p6 = " << p6 << "\np22 += p6 = " << p22 << std::endl;

    p22 -= p6;
    std::cout << "\np22 -= p6 => p22 = " << p22 << std::endl;

    p22 -= p6;
    std::cout << "p22 -= p6 => p22 = " << p22 << std::endl;

    std::cout << "p22 * 2 = " << p22 * 2 << std::endl;
    std::cout << "2.5 * p22 = " << 2.5 * p22 << std::endl;

    return 0;
}
