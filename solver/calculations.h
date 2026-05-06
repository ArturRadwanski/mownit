//
// Created by valleron on 5/5/26.
//

#ifndef SOLVER_CALCULATIONS_H
#define SOLVER_CALCULATIONS_H
long double given_function(long double x);
long double given_differential(long double x);
long double newton_method(long double start, int max_iterations, bool stop_fx, long double rho, bool& out_of_bounds, bool& end_naturally);
#endif //SOLVER_CALCULATIONS_H