#include "Polynomial.h"
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <utility>

template<typename T>
Polynomial<T>::Polynomial(const unsigned int degree) 
{
    std::cout << "\nBase template" << std::endl;
    this->size = degree + 1;
    coefficients = new T[size]();
}

template<typename T>
Polynomial<T>::Polynomial(const unsigned int degree , const T* coefficients) : Polynomial(degree) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = coefficients[i];
    }
}

template<typename T>
Polynomial<T>::Polynomial(std::initializer_list<T> list) : Polynomial(list.size() - 1) 
{
    unsigned int i = 0;
    for (auto item : list)
    {
        this->coefficients[i++] = item;
    }
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& p) : Polynomial(p.size - 1) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = p.coefficients[i];
    }
}

template<typename T>
    template<typename U>
Polynomial<T>::Polynomial(const Polynomial<U>& p) : Polynomial<T>(p.size - 1) 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        this->coefficients[i] = p.coefficients[i];
    }
}

template<typename T>
Polynomial<T>::~Polynomial() 
{
    delete[] coefficients;
}

template<typename T>
T Polynomial<T>::operator[](unsigned int index) const
{
    return coefficients[index];
}

template<typename T>
T& Polynomial<T>::operator[](unsigned int index)
{
    return coefficients[index];
}

template<typename T>
T Polynomial<T>::operator()(T x) const 
{
    double result = coefficients[getDegree()];
    for (int i = getDegree() - 1; i >= 0; i--) 
    {
        result = result * x + coefficients[i];
    }
    return result;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& other) 
{
    if (size != other.size) 
    {
        T* tmp = new T[other.size];
        delete coefficients;
        coefficients = tmp;
        size = other.size;
    }

    std::copy(other.coefficients, other.coefficients + other.size, coefficients);
    return *this;
}

template<typename T>
    template<typename U>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<U>& other) 
{
    return Polynomial<T>::operator=((Polynomial<T>)other);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator++() 
{
    for (unsigned int i = 0; i < size; i++) 
    {
        coefficients[i] += 1;
    }
    return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator++(int d) 
{
    Polynomial<T> old = *this;
    operator++();
    return old;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator--() 
{
    for (unsigned int i = 0; i < size; i++) {
        coefficients[i] -= 1;
    }
    return *this;
}

template<typename T>
Polynomial<T> Polynomial<T>::operator--(int d) 
{
    Polynomial<T> old = *this;
    operator++();
    return old;
}

template<typename T1, typename T2>
Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>& p, T2 value) 
{
    Polynomial<decltype(T1() * T2())> tmp(p.getDegree());
    for (unsigned int i = 0; i < p.size; i++)
    {
        tmp.coefficients[i] = p.coefficients[i] * value;
    }
    return tmp;
}

template<typename T1,typename T2>
Polynomial<decltype(T1() * T2())> operator*(T1 value, const Polynomial<T2>& p) 
{
    return p * value;
}

template<typename U>
Polynomial<U> operator-(Polynomial<U>& p1, Polynomial<U>& p2) 
{
    return p1 + (-1) * p2;
}

template<typename T1, typename T2>
Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>& lhs, const Polynomial<T2>& rhs)
{
    Polynomial<decltype(T1() * T2())> tmp(lhs.getDegree() + rhs.getDegree());
    for (unsigned int i = 0; i < lhs.size; i++) 
    {
        for (unsigned int j = 0; j < rhs.size; j++) 
        {
            tmp.coefficients[i+j] += lhs.coefficients[i] * rhs.coefficients[j];
        }
    }
    return tmp;
}

template<typename T>
    template<typename U>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<U>& rhs) {
    return Polynomial<T>::operator+=((Polynomial<T>)rhs);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& rhs) {
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

template<typename U>
std::istream& operator>>(std::istream& is, const Polynomial<U>& p) 
{
    for (unsigned int i = 0; i < p.size; i++) 
    {
        std::cout << "c[" << i << "] = ";
        is >> p.coefficients[i];
    }
    return is;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Polynomial<U>& p) 
{
    for (unsigned int i = 0; i < p.size; i++) 
    {
        os << p.coefficients[p.size - 1 - i] << "x^" << p.size - 1 - i;
        if (i < p.size - 1) 
        {
            os << " + ";
        }
    }
    return os;
}

template<typename T>
void Polynomial<T>::resize(const unsigned int size) 
{
    T* tmp = new T[size]();
    if (tmp == nullptr) throw std::runtime_error("Error: couldn`t allocate memmory in resize method");
    for (unsigned int i = 0; i < this->size; i++) 
    {
        tmp[i] = coefficients[i];
    }
    delete[] coefficients;
    coefficients = tmp;
    this->size = size;
}

template<typename T1, typename T2>
Polynomial<decltype(T1() + T2())> operator+(const Polynomial<T1>& p1, const Polynomial<T2>& p2) 
{
    const unsigned int degree = std::max(p1.getDegree(), p2.getDegree());
    Polynomial<decltype(T1() + T2())> result(degree);
    for (unsigned int i = 0; i < result.getSize(); i++) 
    {
        double value1 = (i < p1.getSize()) ? p1[i] : 0;
        double value2 = (i < p2.getSize()) ? p2[i] : 0;
        result[i] = value1 + value2;
    }
    return result;
}

template<typename U>
Polynomial<U> substraction(const Polynomial<U>& p1, const Polynomial<U>& p2) 
{
    const unsigned int degree = std::max(p1.size, p2.size) - 1;
    Polynomial<U> result(degree);
    for (unsigned int i = 0; i < result.size; i++) 
    {
        double value1 = (i < p1.size) ? p1.coefficients[i] : 0;
        double value2 = (i < p2.size) ? p2.coefficients[i] : 0;
        result.coefficients[i] = value1 - value2;
    }
    return result;
}

template<typename U>
Polynomial<U> operator-=(Polynomial<U>& lhs, const Polynomial<U>& rhs) {
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