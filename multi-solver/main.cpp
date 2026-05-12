//
// Created by valleron on 5/12/26.
//

#include <fstream>
#include <iostream>
#include <ostream>
#include "calculations.h"
#include "tests.h"

void test_task_1() {

}

int main() {

    std::ofstream file("results_float_3_thomas.txt");
    tests_thomas_task<float>(1000, 1e-8f, file);

    std::ofstream file2("results_double_3_thomas.txt");
    tests_thomas_task<double>(1000, 1e-16, file2);

    std::ofstream file3("results_long_3_thomas.txt");
    tests_thomas_task<long double>(1000, 1e-22L, file3);

    file.close();
    file2.close();
    file3.close();
    return 0;
}
