#include "Polynomial.h"
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <utility>

Polynomial<double>::Polynomial(const unsigned int degree) 
{
    std::cout << "\nFull double spec" << std::endl;
    this->size = degree + 1;
    coefficients = new double[size]();
}


Polynomial<double>::Polynomial(const unsigned int degree , const double* coefficients) : Polynomial(degree) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = coefficients[i];
    }
}


Polynomial<double>::Polynomial(std::initializer_list<double> list) : Polynomial(list.size() - 1) 
{
    unsigned int i = 0;
    for (auto item : list)
    {
        this->coefficients[i++] = item;
    }
}


Polynomial<double>::Polynomial(const Polynomial<double>& p) : Polynomial(p.size - 1) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = p.coefficients[i];
    }
}


Polynomial<double>::~Polynomial() 
{
    delete[] coefficients;
}


double Polynomial<double>::operator[](unsigned int index) const
{
    return coefficients[index];
}


double& Polynomial<double>::operator[](unsigned int index)
{
    return coefficients[index];
}


double Polynomial<double>::operator()(double x) const 
{
    double result = coefficients[getDegree()];
    for (int i = getDegree() - 1; i >= 0; i--) 
    {
        result = result * x + coefficients[i];
    }
    return result;
}


template<typename U>
Polynomial<double>& Polynomial<double>::operator=(const Polynomial<U>& other) 
{
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


Polynomial<double>& Polynomial<double>::operator++() 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        coefficients[i] += 1;
    }
    return *this;
}


Polynomial<double> Polynomial<double>::operator++(int d) 
{
    Polynomial<double> old = *this;
    operator++();
    return old;
}


Polynomial<double>& Polynomial<double>::operator--() 
{
    for (unsigned int i = 0; i < size; i++) {
        coefficients[i] -= 1;
    }
    return *this;
}


Polynomial<double> Polynomial<double>::operator--(int d) 
{
    Polynomial<double> old = *this;
    operator++();
    return old;
}

Polynomial<double>& Polynomial<double>::operator+=(const Polynomial<double>& rhs) {
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

void Polynomial<double>::resize(const unsigned int size) 
{
    double* tmp = new double[size]();
    if (tmp == nullptr) throw std::runtime_error("Error: couldn`double allocate memmory in resize method");
    for (unsigned int i = 0; i < this->size; i++) 
    {
        tmp[i] = coefficients[i];
    }
    delete[] coefficients;
    coefficients = tmp;
    this->size = size;
}

