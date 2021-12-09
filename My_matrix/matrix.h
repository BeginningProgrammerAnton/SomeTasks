#pragma once

#include <vector>

class Matrix {
public:
    Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
        Zeros();
    }
    Matrix(int n) : Matrix(n, n) {
    }
    Matrix(std::vector<std::vector<double>> m)
        : matrix_(m), rows_(m.size()), columns_(m.back().size()) {
    }
    size_t Rows() const {
        return rows_;
    }
    size_t Columns() const {
        return columns_;
    }
    double& operator()(int a, int b) {
        return matrix_[a][b];
    }
    const double& operator()(int a, int b) const {
        return matrix_[a][b];
    }
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        Matrix mat(lhs.Rows(), lhs.Columns());
        for (size_t i = 0; i < lhs.Rows(); ++i) {
            for (size_t j = 0; j < lhs.Columns(); j++) {
                mat(i, j) = lhs(i, j) + rhs(i, j);
            }
        }
        return mat;
    }
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        Matrix mat(lhs.Rows(), lhs.Columns());
        for (size_t i = 0; i < lhs.Rows(); ++i) {
            for (size_t j = 0; j < lhs.Columns(); j++) {
                mat(i, j) = lhs(i, j) - rhs(i, j);
            }
        }
        return mat;
    }
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        Matrix mat(lhs.Rows(), rhs.Columns());
        for (size_t i = 0; i < lhs.Rows(); i++) {
            for (size_t j = 0; j < rhs.Columns(); j++) {
                for (size_t k = 0; k < lhs.Columns(); k++) {
                    mat(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
        return mat;
    }
    Matrix& operator+=(const Matrix& rhs) {
        return *this = *this + rhs;
    }
    Matrix& operator-=(const Matrix& rhs) {
        return *this = *this - rhs;
    }
    Matrix& operator*=(const Matrix& rhs) {
        return *this = *this * rhs;
    }

private:
    size_t rows_;
    size_t columns_;
    std::vector<std::vector<double>> matrix_;
    void Zeros() {
        std::vector<double> mat;
        for (int j = 0; j < columns_; j++) {
            mat.push_back(0);
        }
        for (int i = 0; i < rows_; ++i) {
            matrix_.push_back(mat);
        }
    }
};

Matrix Transpose(const Matrix& mat) {
    Matrix mat1(mat.Columns(), mat.Rows());
    for (int i = 0; i < mat.Columns(); ++i) {
        for (int j = 0; j < mat.Rows(); j++) {
            mat1(i, j) = mat(j, i);
        }
    }
    return mat1;
}
Matrix Identity(int n) {
    Matrix mat(n);
    for (int i = 0; i < mat.Rows(); ++i) {
        mat(i, i) = 1;
    }
    return mat;
}