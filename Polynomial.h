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

    int getCoefficientAt(unsigned int) const;
    void setCoefficientAt(unsigned int, int);
    int calculate(int value) const;

    Polynomial& operator+(const Polynomial&);
    Polynomial& operator-(const Polynomial&);
    Polynomial& operator*(const Polynomial&);
    int operator()(int x);

    friend Polynomial substraction(const Polynomial&, const Polynomial&);
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
private:
    void resize(const unsigned int);
    int* coefficients{};
    unsigned int size = 1;
};

#endif //POLYNOMIAL_H