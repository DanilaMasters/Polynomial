#include "Polynomial.h"
#include <initializer_list>
#include <stdexcept>
#include <iostream>

Polynomial::Polynomial(const unsigned int degree) 
{
    this->size = degree + 1;
    coefficients = new double[size]();
}

Polynomial::Polynomial(const unsigned int degree , const int* coefficients) : Polynomial(degree) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = coefficients[i];
    }
}

Polynomial::Polynomial(std::initializer_list<int> list) : Polynomial(list.size() - 1) 
{
    unsigned int i = 0;
    for (auto item : list)
    {
        this->coefficients[i++] = item;
    }
}

Polynomial::Polynomial(const Polynomial& p) : Polynomial(p.size - 1) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = p.coefficients[i];
    }
}

Polynomial::~Polynomial() 
{
    delete[] coefficients;
}

double Polynomial::operator[](unsigned int index) const
{
    return coefficients[index];
}

double& Polynomial::operator[](unsigned int index)
{
    return coefficients[index];
}

double Polynomial::operator()(double x) const 
{
    double result = coefficients[getDegree()];
    for (int i = getDegree() - 1; i >= 0; i--) 
    {
        result = result * x + coefficients[i];
    }
    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& other) 
{
    if (this == &other) 
    {
        return *this;
    }

    if (size != other.size) 
    {
        double* tmp = new double[other.size];
        delete coefficients;
        coefficients = tmp;
        size = other.size;
    }

    std::copy(other.coefficients, other.coefficients + other.size, coefficients);
    return *this;
}

Polynomial& Polynomial::operator++() 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        coefficients[i] += 1;
    }
    return *this;
}

Polynomial Polynomial::operator++(int d) 
{
    Polynomial old = *this;
    operator++();
    return old;
}

Polynomial& Polynomial::operator--() 
{
    for (unsigned int i = 0; i < size; i++) {
        coefficients[i] -= 1;
    }
    return *this;
}

Polynomial Polynomial::operator--(int d) 
{
    Polynomial old = *this;
    operator++();
    return old;
}

Polynomial Polynomial::operator+(const Polynomial& p) 
{
    Polynomial tmp(p.size > size ? p.size : size);
    for (unsigned int i = 0; i < size; i++) 
    {
        tmp.coefficients[i] += coefficients[i]; 
    }
    for (unsigned int i = 0; i < p.size;  i++) 
    {
        tmp.coefficients[i] += p.coefficients[i];
    }
    return tmp;
}

Polynomial operator*(const Polynomial& p, double value) 
{
    Polynomial tmp(p.size);
    for (unsigned int i = 0; i < p.size; i++)
    {
        tmp.coefficients[i] = p.coefficients[i] * value;
    }
    return tmp;
}

Polynomial operator*(double value, const Polynomial& p) 
{
    return p * value;
}

Polynomial operator-(Polynomial& p1, Polynomial& p2) 
{
    return p1 + (-1) * p2;
}

Polynomial Polynomial::operator*(Polynomial& p)
{
    Polynomial tmp(size + p.size);
    for (unsigned int i = 0; i < size; i++) 
    {
        for (unsigned int j = 0; j < p.size; j++) 
        {
            tmp.coefficients[i+j] += coefficients[i] * p.coefficients[j];
        }
    }
    return tmp;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    unsigned int j;
    if (rhs.size > size) {
        resize(rhs.size);
        j = size;
    } else {
        j = rhs.size;
    }
    for (unsigned int i = 0; i < j; i++) {
        double num1 = i < rhs.size ? rhs.coefficients[i] : 0;
        double num2 = i < size ? coefficients[i] : 0;
        coefficients[i] = num1 + num2;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, const Polynomial& p) 
{
    for (unsigned int i = 0; i < p.size; i++) 
    {
        std::cout << "c[" << i << "] = ";
        is >> p.coefficients[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) 
{
    for (unsigned int i = 0; i < p.size; i++) 
    {
        if (p.coefficients[p.size - 1 - i] != 0) 
        {
            os << p.coefficients[p.size - 1 - i] << "x^" << p.size - 1 - i;
            if (i < p.size - 1) 
            {
                os << " + ";
            }
        }
    }
    return os;
}

void Polynomial::resize(const unsigned int size) 
{
    double* tmp = new double[size]();
    if (tmp == nullptr) throw std::runtime_error("Error: couldn`t allocate memmory in resize method");
    for (unsigned int i = 0; i < this->size; i++) 
    {
        tmp[i] = coefficients[i];
    }
    delete[] coefficients;
    coefficients = tmp;
    this->size = size;
}

Polynomial addition(const Polynomial& p1, const Polynomial& p2) 
{
    const unsigned int degree = std::max(p1.getDegree(), p2.getDegree());
    Polynomial result(degree);
    for (unsigned int i = 0; i < result.getSize(); i++) 
    {
        double value1 = (i < p1.getSize()) ? p1[i] : 0;
        double value2 = (i < p2.getSize()) ? p2[i] : 0;
        result[i] = value1 + value2;
    }
    return result;
}

Polynomial substraction(const Polynomial& p1, const Polynomial& p2) 
{
    const unsigned int degree = std::max(p1.size, p2.size) - 1;
    Polynomial result(degree);
    for (unsigned int i = 0; i < result.size; i++) 
    {
        double value1 = (i < p1.size) ? p1.coefficients[i] : 0;
        double value2 = (i < p2.size) ? p2.coefficients[i] : 0;
        result.coefficients[i] = value1 - value2;
    }
    return result;
}

Polynomial operator-=(Polynomial& lhs, const Polynomial& rhs) {
    unsigned int j;
    if (rhs.size > lhs.size) {
        lhs.resize(rhs.size);
        j = rhs.size;
    } else {
        j = lhs.size;
    }
    for (unsigned int i = 0; i < j; i++) {
        double value1 = (i < lhs.size) ? lhs.coefficients[i] : 0;
        double value2 = (i < rhs.size) ? rhs.coefficients[i] : 0;
        lhs.coefficients[i] = value1 - value2;   
    }

    return lhs;
}