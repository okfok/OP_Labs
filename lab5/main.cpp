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

    auto **array = new TMatrix *[2];

    std::cout << "Matrix A:\n";
    array[0] = input_matrix_from_console(3, 3); // A

    std::cout << "Matrix B:\n";
    array[1] = input_matrix_from_console(2, 2); // B


    std::cout << "A:\n" << array[0]->to_str();

    std::cout << "B:\n" << array[1]->to_str();

    std::cout << "\nAnswer: " << (array[0]->sum() + array[0]->determinant() + array[1]->determinant()) << '\n';


    delete array[0];
    delete array[1];
    delete[] array;


}
