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

double TMatrix::get_element(int row, int col) {
    if ((0 <= row && row < _row) && (0 <= col && col < _col)) {
        return _matrix[row][col];
    } else {
        throw;
    }
}

void TMatrix::set_element(int row, int col, double value) {
    if ((0 <= row && row < _row) && (0 <= col && col < _col)) {
        _matrix[row][col] = value;
    } else {
        throw;
    }
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

void TMatrix::input_from_console() {
    std::cout << "Enter numbers of " << _row << 'x' << _col << " matrix:\n";

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            std::cin >> _matrix[i][j];
        }
    }
}

void TMatrix::print_to_console() {
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            std::cout << _matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "Sum: " << sum() << '\n';
}

void SquareMatrix::print_to_console() {
    TMatrix::print_to_console();
    std::cout << "Det: " << determinant() << '\n';
}


long double SquareMatrix::determinant() {
    if (_row <= 1)
        throw;

    if (_row == 2)
        return (_matrix[0][0] * _matrix[1][1]) - (_matrix[1][0] * _matrix[0][1]);


    long double det = 0;


    for (int x = 0; x < _row; x++) {
        double **submatrix = create_matrix(_row - 1, _row - 1);

        int subi = 0;
        for (int i = 1; i < _row; i++) {
            int subj = 0;
            for (int j = 0; j < _row; j++) {
                if (j == x)
                    continue;
                submatrix[subi][subj] = _matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (((x % 2) ? -1 : 1) * _matrix[0][x] * SquareMatrix(submatrix, _row - 1).determinant());
        submatrix = nullptr;
    }

    return det;
}


long double Matrix_2::determinant() {
    return (_matrix[0][0] * _matrix[1][1]) - (_matrix[1][0] * _matrix[0][1]);
}

