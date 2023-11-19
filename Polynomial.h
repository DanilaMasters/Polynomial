#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
public:
    Polynomial() = default;
    Polynomial(const unsigned int);
    Polynomial(const unsigned int, const int*);
    Polynomial(std::initializer_list<int>);
    Polynomial(const Polynomial&);
    ~Polynomial();

    inline unsigned int getDegree() const { return size - 1; }
    inline unsigned int getSize() const { return size; }

    double getCoefficientAt(unsigned int) const;
    void setCoefficientAt(unsigned int, double);

    Polynomial operator+(const Polynomial&);
    Polynomial operator-(const Polynomial&);
    Polynomial operator*(const Polynomial&);
    double operator()(double x);

    friend Polynomial substraction(const Polynomial&, const Polynomial&);
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
private:
    void resize(const unsigned int);
    double* coefficients{};
    unsigned int size = 1;
};

#endif //POLYNOMIAL_H