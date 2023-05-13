#include "TMatrix.h"


double **create_matrix(int row, int col, bool fill_with_zero = true) {
    auto matrix = new double *[row];

    for (int i = 0; i < row; ++i) {
        matrix[i] = new double[col];
        if (fill_with_zero) {
            for (int j = 0; j < col; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

TMatrix::TMatrix(int row, int col) : _row(row), _col(col), _matrix(create_matrix(row, col)) {}

TMatrix::TMatrix(TMatrix &other) : _row(other._row), _col(other._col) {
    _matrix = create_matrix(_row, _row, false);

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

TMatrix::~TMatrix() {
    for (int i = 0; i < _row; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

long double TMatrix::sum() {
    long double sum = 0;
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            sum += _matrix[i][j];
        }
    }

    return sum;
}

std::string TMatrix::to_str() {
    std::string str = "Matrix(" + std::to_string(_row) + 'x' + std::to_string(_col) + "):\n";

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            str += std::to_string(_matrix[i][j]) + ' ';
        }
        str += '\n';
    }

    return str + "Sum: " + std::to_string(sum()) + '\n';

}


long double Matrix_2::determinant() {
    return (_matrix[0][0] * _matrix[1][1]) - (_matrix[1][0] * _matrix[0][1]);
}

long double Matrix_3::determinant() {

    long double det = 0;

    for (int x = 0; x < _row; x++) {
        Matrix_2 submatrix;

        int subi = 0;
        for (int i = 1; i < _row; i++) {
            int subj = 0;
            for (int j = 0; j < _row; j++) {
                if (j == x)
                    continue;
                submatrix.element(subi, subj) = _matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (((x % 2) ? -1 : 1) * _matrix[0][x] * submatrix.determinant());
    }

    return det;
}

std::string Matrix_2::to_str() { return TMatrix::to_str() + "Det: " + std::to_string(determinant()) + '\n'; }

std::string Matrix_3::to_str() { return TMatrix::to_str() + "Det: " + std::to_string(determinant()) + '\n'; }


TMatrix *input_matrix_from_console(int row, int col) {
    std::cout << "Enter numbers of " << row << 'x' << col << " matrix:\n";

    TMatrix *matrix;

    if (row == 2 && col == 2)
        matrix = new Matrix_2;
    else if (row == 3 && col == 3)
        matrix = new Matrix_3;
    else
        matrix = new Matrix(row, col);


    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cin >> matrix->element(i, j);

        }
    }


    return matrix;
}