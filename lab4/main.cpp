#include <iostream>
#include "Polynomial.h"


int main() {
    double coefs[] = {2, 0, 0, -7};
    Polynomial p1(coefs); // 2x^3 - 7
    std::cout << "p1: " << p1.to_str() << '\n';

    Polynomial p2(1, 2, 3, 4); // x^3 + 2x^2 + 3x + 4
    std::cout << "p2: " << p2.to_str() << '\n';

    Polynomial p3(3); // x^3
    std::cout << "p3: " << p3.to_str() << '\n';


    Polynomial p4 = p1 + p2; // sum of p1 and p2
    std::cout << "p4: " << p4.to_str() << '\n';

    Polynomial p5 = p2 * p3; // product of p2 and p3
    std::cout << "p5: " << p5.to_str() << '\n';


}
