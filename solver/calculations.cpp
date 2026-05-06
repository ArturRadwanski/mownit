//
// Created by valleron on 5/5/26.
//

#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>

long double given_function(const long double x) {
    return x * 0.000016701700790245659312 - 30 * expl(-11 * x) + 0.03333333333333333287;
}

long double given_differential(const long double x) {
    return x * 0.000016701700790245659312 + 330 * expl(-11 * x);
}

long double newton_method(long double start, const int max_iterations, const bool stop_fx, const long double rho, bool& out_of_bounds, bool& end_naturally) {
    out_of_bounds = false;
    end_naturally = false;
    for (int i=0;i<max_iterations;i++) {
        const long double last = start;
        start = start - given_function(start) / given_differential(start);
        out_of_bounds = out_of_bounds  || start < 0;


        if ((stop_fx && fabsl(given_function(start)) < rho) ||
            (!stop_fx && fabsl(start - last) < rho)) {
            end_naturally = true;
            break;
        }
    }
    return start;
}
