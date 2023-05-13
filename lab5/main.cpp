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

    array[0] = new Matrix_3; // A

    std::cout << "Matrix A:\n";
    array[0]->input_from_console();

    array[1] = new Matrix_2; // B

    std::cout << "Matrix B:\n";
    array[1]->input_from_console();


    std::cout << "Matrix A:\n";
    array[0]->print_to_console();

    std::cout << "Matrix B:\n";
    array[1]->print_to_console();

    std::cout << "\nAnswer: " << (array[0]->sum() + array[0]->determinant() + array[1]->determinant()) << '\n';


    delete array[0];
    delete array[1];
    delete[] array;


}
