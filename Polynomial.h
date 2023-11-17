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
    inline void setDegree(int value) { degree = value; }

    int coefficientAt(unsigned int);
    void coefficientInsert(unsigned int, int);
private:
    Coefficients coefficients;
    unsigned int degree{};
};

#endif //POLYNOMIAL_H