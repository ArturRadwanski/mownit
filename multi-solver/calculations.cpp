//
// Created by valleron on 5/12/26.
//
#include "calculations.h"
#include <eigen3/Eigen/Dense>

long double calculate_condition_index(const std::vector<long double>& matrix, const int n) {
    Eigen::Matrix<long double,Eigen::Dynamic, Eigen::Dynamic> A(n, n);
    for (int i = 0; i < n*n; i++) {
        A(i%n, i / n) = matrix[i];
    }
    const long double norm_inf = A.lpNorm<Eigen::Infinity>();
    const Eigen::Matrix<long double,Eigen::Dynamic, Eigen::Dynamic> A_inv = A.inverse();
    const long double norm_inf_inv = A_inv.lpNorm<Eigen::Infinity>();
    return norm_inf * norm_inf_inv;
}

