#include "Polynomial.h"
#include <stdexcept>

Coefficients::Coefficients(int size) {
    this->size = size;
    values = new int[size]();
}

Coefficients::Coefficients(int size, int* values) : Coefficients(size) {
    for (int i = 0; i < size; i++) {
        this->values[i] = values[i];
    }
}

int Coefficients::at(unsigned int index) {
    if (index >= size) throw std::runtime_error("Index exceeds array size.\n");
    return values[index];
}

void Coefficients::insert(unsigned int index, int value) {
    if (index >= size) throw std::runtime_error("Error: index exceed coefficients array size");
    values[index] = value;
}