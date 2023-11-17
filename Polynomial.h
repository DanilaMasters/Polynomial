#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
public:
    Polynomial() = default;
    Polynomial(unsigned int);
    Polynomial(unsigned int, const int*);
    Polynomial(const Polynomial&);
    ~Polynomial();

    inline unsigned int getDegree() { return degree; }
    inline unsigned int getSize() { return size; }
    inline void setDegree(int value) { degree = value; }

    int coefficientAt(unsigned int);
    void coefficientInsert(unsigned int, int);

    Polynomial& operator+(const Polynomial&);
private:
    int* coefficients{};
    unsigned int size{};
    unsigned int degree{};
};

#endif //POLYNOMIAL_H