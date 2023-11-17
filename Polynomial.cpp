#include "Polynomial.h"

Polynomial::Polynomial(unsigned int degree) {
    this->degree = degree;
    this->size = degree + 1;
    coefficients = new int[size]();                 //zero initialization
}

Polynomial::Polynomial(unsigned int degree, const int* coefficients) : Polynomial(degree) {
    for (unsigned int i = 0; i < size; i++) {
        this->coefficients[i] = coefficients[i];
    }
}

Polynomial::Polynomial(const Polynomial& p) : Polynomial(p.degree) {
    for (unsigned int i = 0; i < size; i++) {
        this->coefficients[i] = p.coefficients[i];
    }
}

Polynomial::~Polynomial() {
    delete[] coefficients;
}

int Polynomial::coefficientAt(unsigned int index) { 
    if (index >= size) throw std::runtime_error("Index exceeds array size.\n");
    return coefficients[index];
}

void Polynomial::coefficientInsert(unsigned int index, int value) {
    if (index >= size) throw std::runtime_error("Error: index exceed coefficients array size");
    coefficients[index] = value;
}

Polynomial& Polynomial::operator+(const Polynomial& p) {
    for (int i = 0; i < size; i++) {
        this->coefficients[i] += p.coefficients[i];
    }
}