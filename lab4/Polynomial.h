#ifndef LAB4_POLYNOMIAL_H
#define LAB4_POLYNOMIAL_H

#include <cmath>
#include <cstdarg>
#include <iostream>


class Polynomial {
    const int degree;
    double *a;

    Polynomial(int degree, double *a) : degree(degree), a(a) {}

public:

    Polynomial(double a, double b, double c, double d);

    Polynomial(const double coefs[4]);

    Polynomial(int degree);

    Polynomial() : degree(0), a(nullptr) {};

    Polynomial(const Polynomial &);

    ~Polynomial();

    Polynomial operator+(Polynomial other) const;

    Polynomial operator*(Polynomial other) const;


    double enumerate(double x) const;

    double get_coef(int num);

    void set_coef(int i, double coef);

    int get_degree() { return degree; }

    std::string to_str();


};


#endif //LAB4_POLYNOMIAL_H
