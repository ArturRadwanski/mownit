#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include "calculations.h"
constexpr long double real_x = 0.6183713614281612966421;

void check_newton(std::ofstream& file, const bool stop_fx, const std::string& table_title) {
    file << "\\begin{table}[h!]\n\\centering\n\\footnotesize\n";
    file << "\\begin{tabular}{l|" << "c|c|c|c|c|c|c|c|c|" << "}\n\\toprule\n";
    file << "$x_0$";
    for (int j = 1; j < 10; j++) file << " & $\\rho=10^{-" << 2*j << "}$";
    file << " \\\\\n\\midrule\n";

    for (int i = 0; i <= 20; i++) {
        long double start = 0.1L * i;
        file << std::fixed << std::setprecision(1) << start;

        for (int j = 1; j < 10; j++) {
            const long double rho = std::pow(0.01L, j);
            bool out_of_bounds = false;
            bool end_naturally = false;
            const long double x = newton_method(start, 1e6, stop_fx, rho, out_of_bounds, end_naturally);
            const long double err = std::fabsl(x - real_x);

            file << " & ";
            if (out_of_bounds) file << "\\cellcolor{red!25}";
            if (!end_naturally) file << "\\underline{";
            file << std::scientific << std::setprecision(2) << err;
            if (!end_naturally) file << "}";
        }
        file << " \\\\\n";
    }
    file << "\\bottomrule\n\\end{tabular}";
    file << "\\caption{" << table_title << "}\n\\end{table}";
}

int main() {
    std::ofstream file("tabela_wynikow_fx.tex");
    check_newton(file, true, "wyniki dla stopu fx");
    file.close();

    std::ofstream file2("tabela_wynikow_x.tex");
    check_newton(file2, true, "wyniki dla stopu x");
    file2.close();
    return 0;
}