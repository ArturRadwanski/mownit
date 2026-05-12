//
// Created by valleron on 5/12/26.
//
#pragma once
#ifndef MULTI_SOLVER_CALCULATIONS_H
#define MULTI_SOLVER_CALCULATIONS_H
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>

template <typename T>
std::vector<T> gauss(std::vector<T>& A, std::vector<T>& B, int n, bool max_pivot, T eps, bool& unique_solution);
template <typename T>
std::vector<T> build_matrix_1(int n);
template <typename T>
std::vector<T> build_matrix_2(int n);
template <typename T>
std::vector<T> build_matrix_3(int n);
template <typename T>
std::tuple<std::vector<T>, std::vector<T>, std::vector<T>> build_matrix_thomas(int n);
template <typename T>
std::vector<T> thomas_algorithm(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C, std::vector<T>& D,  const int n);




template <typename T>
void swap_rows(std::vector<T>& A, int i, int j, int n);
template <typename T>
void subtract_rows(std::vector<T>& A, T scalar, int j, int i, int n);
template <typename T>
std::vector<T> build_solution_matrix(int n, int j);
template <typename T>
std::vector<T> multiply_matrix(const std::vector<T>& A, const std::vector<T>& B, int n);
template <typename T>
void print_square_matrix(const std::vector<T>& A,   int n);
long double calculate_condition_index(const std::vector<long double>& matrix, int n);


template <typename T>
std::vector<T> gauss(std::vector<T>& A, std::vector<T>& B, const int n, const bool max_pivot, T eps, bool& unique_solution) {
    unique_solution = true;
    for (int i = 0; i < n-1; i++) {
        int p = i;
        if (!max_pivot) {
            while (fabs(A[i*n + p]) < eps) {
                p++;
                if (p == n) {
                    unique_solution = false;
                    return std::vector<T>(NULL);
                }
            }
        }
        else {
            T max_val = std::fabs(A[i * n + i]);

            for (int k = i + 1; k < n; k++) {
                if (std::fabs(A[k * n + i]) > max_val) {
                    max_val = std::fabs(A[k * n + i]);
                    p = k;
                }
            }

            if (std::fabs(max_val) < eps) { //
                unique_solution = false;
                return {};
            }
        }

        if (p > i) {
            swap_rows(A, i, p, n);
            const T temp = B[i];
            B[i] = B[p];
            B[p] = temp;
        }
        for (int j = i+1; j < n; j++) {
            const T scalar = A[j * n + i] / A[i * n + i];
            subtract_rows(A, scalar, j, i, n);
            B[j] -= scalar * B[i];
        }
    }
    if (fabs(A[n * n - 1]) < eps) {
        unique_solution = false;
        return {};
    }
    std::vector<T> X(n);
    X[n-1] = B[n-1] / A[n * n - 1];
    for (int i = n-2; i >=0; i--) {
        X[i] = B[i];
        for (int j = i+1; j < n; j++) {
            X[i] -= A[i*n + j] * X[j];
        }
        X[i] /= A[i*n + i];
    }
    return X;
}
template <typename T>
void swap_rows(std::vector<T>& A, const int i, const int j, const int n) {
    for (int k = 0; k < n; k++) {
        const T temp = A[i*n+k];
        A[i*n+k] = A[j*n+k];
        A[j*n+k] = temp;
    }
}

template <typename T>
void subtract_rows(std::vector<T>& A, const T scalar, const int j, const int i, const int n) {
    for (int k = 0; k < n; k++) {
        A[j*n+k] -= A[i*n+k] * scalar;
    }
}
template <typename T>
std::vector<T> build_matrix_1(const int n) {
    std::vector<T> A(n*n);
    for (int i = 0; i < n; i++) {
        A[i] = 1.0L;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i*n+j] = 1.0L / (i + j + 1.0L);
        }
    }
    return A;
}

template <typename T>
std::vector<T> build_matrix_2(const int n) {
    std::vector<T> A(n*n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[(i - 1)*n + j - 1] = j >= i ? static_cast<T>(2) * static_cast<T>(i) / j : static_cast<T>(2) * static_cast<T>(j) / i;
        }
    }
    return A;
}

template <typename T>
std::vector<T> build_matrix_3(const int n) {
    std::vector<T> A(n*n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                A[(i - 1)*n + j - 1] = static_cast<T>(-2) * i - 4;
            }
            else if (j == i + 1) {
                A[(i - 1)*n + j - 1] = static_cast<T>(i);
            }
            else if (i > 1 && j == i - 1) {
                A[(i - 1)*n + j - 1] = static_cast<T>(2) / i;
            }
            else {
                A[(i - 1)*n + j - 1] = static_cast<T>(0);
            }
        }
    }
    return A;
}

template<typename T>
std::tuple<std::vector<T>, std::vector<T>, std::vector<T>> build_matrix_thomas(int n) {
    std::vector<T> A(n-1), B(n), C(n-1);
    for (int i = 1; i < n; i++) {
        A[i-1] = static_cast<T>(2) / (i + 1);
        B[i-1] = static_cast<T>(-2 * i) - 4;
        C[i-1] = static_cast<T>(i);
    }
    B[n-1] = static_cast<T>(-2 * n) - 4;
    return std::make_tuple(A, B, C);
}

template <typename T>
std::vector<T> build_solution_matrix(int n, int j) {
    std::vector<T> X(n);
    for (int i = 0; i < n; i++) {
        X[i] = i % j == 0 ? static_cast<T>(-1.0) : static_cast<T>(1.0);
    }
    return X;
}
template <typename T>
std::vector<T> multiply_matrix(const std::vector<T>& A, const std::vector<T>& B, const int n) {
    std::vector<T> X(n);
    for (int i = 0; i < n; i++) {
        X[i] = 0.0L;
        for (int j = 0; j < n; j++) {
            X[i] += A[i*n+j] * B[j];
        }
    }
    return X;
}

template <typename T>
void print_square_matrix(const std::vector<T>& A, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i*n+j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
std::vector<T> thomas_algorithm(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C, std::vector<T>& D, const int n) {
    for (int i = 1; i < n; i++) {
        const T w = A[i-1] / B[i - 1];
        B[i] -= w * C[i - 1];
        D[i] -= w * D[i - 1];
    }

    std::vector<T> X(n);
    X[n-1] = D[n-1] / B[n-1];
    for (int i = n-2; i >= 0; i--) {
        X[i] = (D[i] - C[i]*X[i+1]) /  B[i];
    }
    return X;
}
#endif //MULTI_SOLVER_CALCULATIONS_H