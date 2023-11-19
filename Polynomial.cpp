#include "Polynomial.h"
#include <initializer_list>
#include <stdexcept>
#include <iostream>

Polynomial::Polynomial(const unsigned int degree) {
    this->size = degree + 1;
    coefficients = new int[size]();                 //zero initialization
}

Polynomial::Polynomial(const unsigned int degree , const int* coefficients) : Polynomial(degree) {
    for (unsigned int i = 0; i < degree + 1; i++) {
        this->coefficients[i] = coefficients[i];
    }
}

Polynomial::Polynomial(std::initializer_list<int> list) : Polynomial(list.size() - 1) {
    unsigned int i = 0;
    for (auto& item : list) {
        this->coefficients[i++] = item;
    }
}

Polynomial::Polynomial(const Polynomial& p) : Polynomial(p.size - 1) {
    for (unsigned int i = 0; i < size; i++) {
        this->coefficients[i] = p.coefficients[i];
    }
}

Polynomial::~Polynomial() {
    delete[] coefficients;
}

int Polynomial::getCoefficientAt(unsigned int index) const { 
    if (index >= size) throw std::runtime_error("Index exceeds array size.");
    return coefficients[index];
}

void Polynomial::setCoefficientAt(unsigned int index, int value) {
    if (index >= size) throw std::runtime_error("Error: index exceed coefficients array size");
    coefficients[index] = value;
}

Polynomial& Polynomial::operator+(const Polynomial& p) {
    if (size != p.size) resize(std::max(size, p.size));
    for (unsigned int i = 0; i < std::min(size, p.size); i++) {
        this->coefficients[i] += p.coefficients[i];
    }
    return *this;
}

Polynomial& Polynomial::operator-(const Polynomial& p) {
    if (size != p.size) resize(std::max(size, p.size));
    for (unsigned int i = 0; i < std::min(size, p.size); i++) {
        this->coefficients[i] -= p.coefficients[i];
    }
    return *this;
}

Polynomial& Polynomial::operator*(const Polynomial& p) {
    Polynomial tmp(getDegree() + p.getDegree());
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < p.size; j++)
        {
            tmp.coefficients[i+j] += coefficients[i] * p.coefficients[j];
            //res.setCoefficientAtIndex(i + j, res.getCoefficientAtIndex(i + j) + p1.getCoefficientAtIndex(i) * p2.getCoefficientAtIndex(j));
        }
    }
    resize(tmp.size);
    for (unsigned int i = 0; i < this->size; i++) {
        coefficients[i] = tmp.coefficients[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    for (unsigned int i = 0; i < p.size; i++) {
        os << p.coefficients[i] << " ";
    }
    os << std::endl;
    return os;
}

void Polynomial::resize(const unsigned int size) {
    int* tmp = new int[size]();
    if (tmp == nullptr) throw std::runtime_error("Error: couldn`t allocate memmory in resize method");
    for (unsigned int i = 0; i < this->size; i++) {
        tmp[i] = coefficients[i];
    }
    delete[] coefficients;
    coefficients = tmp;
    this->size = size;
}

Polynomial addition(const Polynomial& p1, const Polynomial& p2) {
    const unsigned int degree = std::max(p1.getDegree(), p2.getDegree());
    Polynomial result(degree);
    for (unsigned int i = 0; i < result.getSize(); i++) {
        int value1 = (i < p1.getSize()) ? p1.getCoefficientAt(i) : 0;
        int value2 = (i < p2.getSize()) ? p2.getCoefficientAt(i) : 0;
        result.setCoefficientAt(i, value1 + value2);
    }
    return result;
}

Polynomial substraction(const Polynomial& p1, const Polynomial& p2) {
    const unsigned int degree = std::max(p1.size, p2.size) - 1;
    Polynomial result(degree);
    for (unsigned int i = 0; i < result.size; i++) {
        int value1 = (i < p1.size) ? p1.coefficients[i] : 0;
        int value2 = (i < p2.size) ? p2.coefficients[i] : 0;
        result.coefficients[i] = value1 - value2;
    }
    return result;
}