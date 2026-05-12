//
// Created by valleron on 5/12/26.
//
#pragma once
#include "calculations.h"
#include <cmath>
#include <iomanip>
#include "Timer.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#ifndef MULTI_SOLVER_TESTS_H
#define MULTI_SOLVER_TESTS_H
template <typename T>
void tests_first_task(int n, T eps, std::ofstream &os);
template <typename T>
long double sqr_err(const std::vector<T>& solutions, const std::vector<T>& X);
template <typename T>
long double max_err(const std::vector<T>& solutions, const std::vector<T>& X);
template <typename T>
void tests_thomas_task(int n, T eps, std::ofstream &os);

int parse_line(char* n);
int get_value();

template <typename T>
void tests_first_task(int n, T eps, std::ofstream &os) {
    Timer t;
    os << std::left << std::setw(6)  << "N"
       << std::setw(20) << "Max Error"
       << std::setw(20) << "RMS Error"
       << std::setw(20) << "Time"
       << std::setw(20) << "Memory (kb)" << std::endl;
    os << std::string(200, '-') << std::endl;

    for (int j = 5; j <= n; j++) {
        if (j>100){j+=99;}
        else if (j>20){j+=9;}
        std::vector<T> A = build_matrix_3<T>(j);
        const std::vector<T> solution = build_solution_matrix<T>(j, 3);
        std::vector<T> B = multiply_matrix(A, solution, j);
        bool unique_solution = true;
        t.reset();
        if (const std::vector<T> X = gauss(A, B, j, false, eps, unique_solution); unique_solution && !X.empty()) {
            const double time = t.elapsed();
            const int memory_usage = get_value();
            const long double m_err = max_err<T>(solution, X);
            const long double s_err = sqr_err<T>(solution, X);

            // Zapis do strumienia (pliku lub konsoli)
            os << std::left << std::setw(6)  << j
               << std::setw(20) << m_err
               << std::setw(20) << s_err
               << std::setw(20) << time
               << std::setw(20) << memory_usage <<std::endl;
        } else {
            os << std::left << std::setprecision(3) << std::setw(6)  << j << " Brak jednoznacznego rozwiazania." << std::endl;
        }
        // std::cout << std::left << std::setw(6)  << j << std::endl;
        // std::cout << std::left << std::string(200, '-') << std::endl;
        // print_square_matrix(A, j);

    }
}

template<typename T>
long double sqr_err(const std::vector<T>& solutions, const std::vector<T>& X) {
    long double error = 0;
    for (std::size_t i = 0; i < solutions.size(); i++) {
        error += (solutions[i] - X[i]) * (solutions[i] - X[i]);
    }
    error = sqrtl(error);
    error /= solutions.size();
    return error;
}

template<typename T>
long double max_err(const std::vector<T>& solutions, const std::vector<T>& X) {
    long double error = 0;
    for (std::size_t i = 0; i < solutions.size(); i++) {
        error = std::max(error, fabsl(solutions[i] - X[i]));
    }
    return error;
}

template <>
inline void tests_first_task<long double>(int n, long double eps, std::ofstream &os) {
    Timer t;
    os << std::left << std::setw(6)  << "N"
       << std::setw(20) << "Cond. Index"
       << std::setw(20) << "Max Error"
       << std::setw(20) << "RMS Error"
       << std::setw(20) << "Time"
       << std::setw(20) << "Memory (kb)" << std::endl;
    os << std::string(200, '-') << std::endl;

    for (int j = 5; j <= n; j++) {
        if (j>100){j+=99;}
        else if (j>20){j+=9;}
        std::vector<long double> A = build_matrix_3<long double>(j);
        const long double conditional_index = calculate_condition_index(A, j);
        const std::vector<long double> solution = build_solution_matrix<long double>(j, 2);
        std::vector<long double> B = multiply_matrix(A, solution, j);
        bool unique_solution = true;
        t.reset();
        if (const std::vector<long double> X = gauss(A, B, j, false, eps, unique_solution); unique_solution && !X.empty()) {
            const double time = t.elapsed();
            const int memory_usage = get_value();
            const long double m_err = max_err<long double>(solution, X);
            const long double s_err = sqr_err<long double>(solution, X);

            // Zapis do strumienia (pliku lub konsoli)
            os << std::left << std::setw(6)  << j
               << std::setw(20) << std::scientific << std::setprecision(6) << conditional_index
               << std::setw(20) << m_err
               << std::setw(20) << s_err
               << std::setw(20) << time
               << std::setw(20) << memory_usage <<std::endl;
        } else {
            os << std::left << std::setprecision(3) << std::setw(6)  << j << " Brak jednoznacznego rozwiazania." << std::endl;
        }
        // std::cout << std::left << std::setw(6)  << j << std::endl;
        // std::cout << std::left << std::string(200, '-') << std::endl;
        // print_square_matrix(A, j);

    }
}
// Source - https://stackoverflow.com/a/64166
// Posted by Lanzelot, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-12, License - CC BY-SA 4.0


inline int parse_line(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

inline int get_value(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parse_line(line);
            break;
        }
    }
    fclose(file);
    return result;
}

template<typename T>
void tests_thomas_task(int n, T eps, std::ofstream &os) {
    Timer t;
    os << std::left << std::setw(6)  << "N"
       << std::setw(20) << "Max Error"
       << std::setw(20) << "RMS Error"
       << std::setw(20) << "Time" << std::endl;
    os << std::string(200, '-') << std::endl;

    for (int j = 5; j <= n; j++) {
        if (j>100){j+=99;}
        else if (j>20){j+=9;}
        std::vector<T> A = build_matrix_3<T>(j);
        const std::vector<T> solution = build_solution_matrix<T>(j, 3);
        std::vector<T> B = multiply_matrix(A, solution, j);
        std::tuple<std::vector<T>, std::vector<T>, std::vector<T>> lines = build_matrix_thomas<T>(j);
        bool unique_solution = true;
        t.reset();
        const std::vector<T> X = thomas_algorithm<T>(std::get<0>(lines), std::get<1>(lines), std::get<2>(lines), B, j);
        const double time = t.elapsed();
        const long double m_err = max_err<T>(solution, X);
        const long double s_err = sqr_err<T>(solution, X);

        // Zapis do strumienia (pliku lub konsoli)
        os << std::left << std::setw(6)  << j
        << std::setw(20) << m_err
        << std::setw(20) << s_err
        << std::setw(20) << time<<std::endl;

        // std::cout << std::left << std::setw(6)  << j << std::endl;
        // std::cout << std::left << std::string(200, '-') << std::endl;
        // print_square_matrix(A, j);

    }
}

#endif //MULTI_SOLVER_TESTS_H