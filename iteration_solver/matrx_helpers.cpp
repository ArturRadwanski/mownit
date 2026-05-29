//
// Created by valleron on 5/28/26.
//

#include <vector>
#include "matrix_helpers.h"
#include <eigen3/Eigen/Dense>
double spectral_vector(const std::vector<double>& matrix, const int n) {
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
    special_matrix(matrix.data(), n, n);
    Eigen::EigenSolver<decltype(special_matrix)> solver(special_matrix);
    auto eigen_values = solver.eigenvalues();

    double spectral_radius = 0.0;
    for (int i = 0; i < n; i++) {
        spectral_radius = std::max(std::abs(eigen_values[i]), spectral_radius);
    }
    return spectral_radius;
}
Eigen::MatrixXd build_matrix(const int n) {
    Eigen::MatrixXd matrix(1);
}