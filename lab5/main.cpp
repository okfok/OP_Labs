#include <iostream>
#include "TMatrix.h"

/*

 A
1 -2 3
2 0 3
1 5 4

 B
3 7
1 -4

*/


int main() {
    Matrix_3 A;

    std::cout << "Matrix A:\n";
    A.input_from_console();

    Matrix_2 B;

    std::cout << "Matrix B:\n";
    B.input_from_console();

    std::cout << "Matrix A:\n";
    A.print_to_console();

    std::cout << "Matrix B:\n";
    B.print_to_console();

    std::cout << "\nAnswer: " << (A.sum() + A.determinant() + B.determinant()) << '\n';


}
