#ifndef LAB5_TMATRIX_H
#define LAB5_TMATRIX_H

#include <iostream>


class TMatrix {
protected:
    double **_matrix;
    const int _row, _col;

    TMatrix(double **matrix, int row, int col) :
            _matrix(matrix), _row(row), _col(col) {}

public:
    TMatrix(int row, int col);

    TMatrix(TMatrix &other);

    ~TMatrix();

    int size_row() { return _row; }

    int size_col() { return _col; }

    double get_element(int row, int col);

    void set_element(int row, int col, double value);

    long double sum();

    void input_from_console();

    virtual void print_to_console();


};

class SquareMatrix : public TMatrix {
protected:

    SquareMatrix(double **matrix, int n) :
            TMatrix(matrix, n, n) {}

public:
    explicit SquareMatrix(int n) : TMatrix(n, n) {};

    long double determinant();

    void print_to_console();
};

class Matrix_2: public SquareMatrix{
public:

    Matrix_2() : SquareMatrix(2) {};
};


class Matrix_3: public SquareMatrix{
public:

    Matrix_3() : SquareMatrix(3) {};
};


#endif //LAB5_TMATRIX_H
