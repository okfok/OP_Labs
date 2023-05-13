#ifndef LAB5_TMATRIX_H
#define LAB5_TMATRIX_H

#include <iostream>


class TMatrix {
protected:
    double **_matrix;
    const int _row, _col;

    TMatrix(int row, int col, double **matrix) :
            _matrix(matrix), _row(row), _col(col) {}

public:
    TMatrix(int row, int col);

    TMatrix(TMatrix &other);

    virtual ~TMatrix();


    int size_row() const { return _row; }

    int size_col() const { return _col; }

    double &element(int row, int col) { return _matrix[row][col]; }


    virtual std::string to_str();


    long double sum();

    virtual long double determinant() = 0;


};


class Matrix : public TMatrix {
public:
    Matrix(int row, int col) : TMatrix(row, col) {}


    long double determinant() override { throw std::logic_error("Function not implemented"); }
};

class Matrix_2 : public TMatrix {
public:

    Matrix_2() : TMatrix(2, 2) {};

    long double determinant() override;

    std::string to_str() override;

};


class Matrix_3 : public TMatrix {
public:

    Matrix_3() : TMatrix(3, 3) {};

    long double determinant() override;

    std::string to_str() override;

};


TMatrix *input_matrix_from_console(int row, int col);


#endif //LAB5_TMATRIX_H
