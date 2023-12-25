#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

template<typename T>
class Polynomial 
{
private:
    void resize(const unsigned int);
    T* coefficients{};
    unsigned int size = 1;
public:
    Polynomial() = default;
    Polynomial(const unsigned int);
    Polynomial(const unsigned int, const T*);
    Polynomial(std::initializer_list<T>);
    Polynomial(const Polynomial&);
    ~Polynomial();

    inline unsigned int getDegree() const { return size - 1; }
    inline unsigned int getSize() const { return size; }

    T getCoefficientAt(unsigned int) const;
    void setCoefficientAt(unsigned int, T);

    // Polynomial operator+(const Polynomial&);
    // Polynomial operator*(Polynomial&);

    T operator[](unsigned int) const;
    T& operator[](unsigned int);
    T operator()(T) const;

    template<typename U>
    Polynomial<T>& operator=(const Polynomial<U>&);
    
    template<typename> friend class Polynomial;

    Polynomial& operator++();
    Polynomial operator++(int);
    Polynomial& operator--();
    Polynomial operator--(int);

    Polynomial& operator+=(const Polynomial&);

    template<typename U>
    friend Polynomial<U> operator-=(Polynomial<U>&, const Polynomial<U>&);

    template<typename U>
    friend Polynomial<U> substraction(const Polynomial<U>&, const Polynomial<U>&);

    template<typename U>
    friend std::istream& operator>>(std::istream&, const Polynomial<U>&);

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<U>&);\
    
    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>&, T2);

    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(T1, const Polynomial<T2>&);

    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>&, const Polynomial<T2>&);
    
    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() + T2())> operator+(const Polynomial<T1>&, const Polynomial<T2>&);

};

template<>
class Polynomial<double> {
    private:
    void resize(const unsigned int);
    double* coefficients{};
    unsigned int size = 1;
public:
    Polynomial() = default;
    Polynomial(const unsigned int);
    Polynomial(const unsigned int, const double*);
    Polynomial(std::initializer_list<double>);
    Polynomial(const Polynomial&);
    ~Polynomial();

    inline unsigned int getDegree() const { return size - 1; }
    inline unsigned int getSize() const { return size; }

    double getCoefficientAt(unsigned int) const;
    void setCoefficientAt(unsigned int, double);

    // Polynomial operator+(const Polynomial&);
    // Polynomial operator*(Polynomial&);

    double operator[](unsigned int) const;
    double& operator[](unsigned int);
    double operator()(double) const;

    template<typename U>
    Polynomial<double>& operator=(const Polynomial<U>&);
    
    template<typename> friend class Polynomial;

    Polynomial& operator++();
    Polynomial operator++(int);
    Polynomial& operator--();
    Polynomial operator--(int);

    Polynomial& operator+=(const Polynomial&);

    template<typename U>
    friend Polynomial<U> operator-=(Polynomial<U>&, const Polynomial<U>&);

    template<typename U>
    friend std::istream& operator>>(std::istream&, const Polynomial<U>&);

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<U>&);
    
    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>&, T2);

    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(T1, const Polynomial<T2>&);

    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() * T2())> operator*(const Polynomial<T1>&, const Polynomial<T2>&);
    
    template<typename T1, typename T2>
    friend Polynomial<decltype(T1() + T2())> operator+(const Polynomial<T1>&, const Polynomial<T2>&);
};

#include "Polynomial.cpp"
#include "PolynomialS.cpp"

#endif //POLYNOMIAL_H