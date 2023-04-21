#include "Polynomial.h"


double Polynomial::enumerate(double x) const {
    double res = 0;
    for (int i = 0; i <= degree; ++i) {
        res += a[i] * pow(x, i);
    }
    return res;
}

Polynomial Polynomial::operator+(Polynomial other) const {
    int max_degree;
    if (degree >= other.degree)
        max_degree = degree;
    else
        max_degree = other.degree;

    auto *b = new double[max_degree + 1];

    for (int i = 0; i <= max_degree; ++i)
        b[i] = 0;

    for (int i = 0; i <= degree; ++i)
        b[i] += a[i];

    for (int i = 0; i <= other.degree; ++i)
        b[i] += other.a[i];


    return Polynomial(max_degree, b);
}


Polynomial Polynomial::operator*(Polynomial other) const {
    int degree = this->degree + other.degree;

    auto *b = new double[degree + 1];

    for (int i = 0; i <= degree; ++i)
        b[i] = 0;


    for (int i = 0; i <= this->degree; ++i) {
        for (int j = 0; j <= other.degree; ++j) {
            b[i + j] += this->a[i] * other.a[j];
        }
    }

    return {degree, b};
}

double Polynomial::get_coef(int num) {
    if (num >= degree)
        throw std::errc::result_out_of_range;

    return a[num];
}

std::string Polynomial::to_str() {
    std::string str;
    for (int i = degree; i >= 0; --i) {
        if (a[i] != 0) {
            if (a[i] > 0 && i != degree)
                str += "+";

            str += std::to_string(a[i]);

            if (i > 1)
                str += "x^" + std::to_string(i);
            else if (i == 1)
                str += "x";

            str += ' ';
        }
    }
    return str;
}

Polynomial::Polynomial(double a, double b, double c, double d) : degree(3) {

    this->a = new double[degree + 1];

    this->a[3] = a;
    this->a[2] = b;
    this->a[1] = c;
    this->a[0] = d;

}

Polynomial::~Polynomial() {
    delete[] a;
}

Polynomial::Polynomial(const Polynomial &other) : degree(other.degree) {

    a = new double[degree + 1];

    for (int i = 0; i <= degree; ++i) {
        a[i] = other.a[i];
    }
}

Polynomial::Polynomial(const double *coefs) : degree(3) {
    a = new double[4];

    for (int i = 0; i < 4; ++i) {
        a[i] = coefs[3 - i];
    }
}

void Polynomial::set_coef(int i, double coef) {
    if (coef >= degree)
        throw std::errc::result_out_of_range;

    a[i] = coef;
}

Polynomial::Polynomial(int degree) : degree(degree) {
    a = new double[degree + 1];

    for (int i = 0; i < degree; ++i) {
        a[i] = 0;
    }
    a[degree] = 1;
}


