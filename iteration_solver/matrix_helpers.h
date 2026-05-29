//
// Created by valleron on 5/28/26.
//
#pragma once

#ifndef ITERATION_SOLVER_MATRIX_HELPERS_H
#define ITERATION_SOLVER_MATRIX_HELPERS_H
#include <vector>
#include <eigen3/Eigen/Dense>
double spectral_vector(std::vector<double> matrix, int n);
Eigen::MatrixXd build_matrix(int n);



#endif //ITERATION_SOLVER_MATRIX_HELPERS_H