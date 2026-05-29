#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>
#include <iomanip>
#include <eigen3/Eigen/Dense>

enum class KryteriumStopu { Przyrostowe, Resydualne };

struct WynikJacobiego {
    Eigen::VectorXd x;
    int liczbaIteracji;
    double czasMs;
};

// --- metoda Jacobiego ---
WynikJacobiego rozwiazJacobi(const Eigen::MatrixXd& A, const Eigen::VectorXd& b,
                             const Eigen::VectorXd& x_0, KryteriumStopu kryterium,
                             double epsilon, int maxIteracji = 10000)
{
    int n = A.rows();
    auto start = std::chrono::high_resolution_clock::now();

    Eigen::VectorXd x = x_0;
    Eigen::VectorXd x_nowe = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd D = A.diagonal();

    int iteracja = 0;
    bool zbieglosc = false;

    for (iteracja = 1; iteracja <= maxIteracji; ++iteracja) {
        Eigen::VectorXd Ax = A * x;
        x_nowe = (b - Ax + D.cwiseProduct(x)).cwiseQuotient(D);

        if (kryterium == KryteriumStopu::Przyrostowe) {
            if ((x_nowe - x).norm() < epsilon) zbieglosc = true;
        } else {
            if ((A * x_nowe - b).norm() < epsilon) zbieglosc = true;
        }

        x = x_nowe;
        if (zbieglosc) break;
    }

    auto koniec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> czasMs = (koniec - start) / iteracja;

    return {x, iteracja, czasMs.count()};
}

// --- FUNKCJA GENERUJĄCA MACIERZ A  ---
Eigen::MatrixXd generujMacierzA(int n, double k = 9.0, double m=1.0) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                A(i, j) = k;
            } else if (j > i) {
                A(i, j) = -m / (j + 1);
            } else { // i > j
                A(i, j) = m / (i + 1);
            }
        }
    }
    return A;
}

// --- FUNKCJA GENERUJĄCA LOSOWĄ PERMUTACJĘ Z {1, -1} ---
Eigen::VectorXd generujWektorReferencyjny(int n) {
    Eigen::VectorXd x_ref(n);
    std::mt19937 g(12345); // Stałe ziarno dla powtarzalności testów
    std::uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < n; ++i) {
        x_ref(i) = dist(g) == 0 ? 1.0 : -1.0;
    }
    return x_ref;
}

// --- ZADANIE 2: OBLICZANIE PROMIENIA SPEKTRALNEGO MACIERZY ITERACJI ---
double obliczPromienSpektralnyJacobiego(const Eigen::MatrixXd& A) {
    int n = A.rows();
    Eigen::MatrixXd D = A.diagonal().asDiagonal();
    Eigen::MatrixXd LU = A - D;

    // Macierz iteracji M_J = -D^(-1) * (L + U)
    Eigen::MatrixXd M_J = -D.inverse() * LU;

    // Obliczanie wartości własnych za pomocą EigenSolver
    Eigen::EigenSolver<Eigen::MatrixXd> solver(M_J);
    const auto& eigenvalues = solver.eigenvalues();

    double maxModul = 0.0;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        double modul = std::abs(eigenvalues[i]);
        if (modul > maxModul) {
            maxModul = modul;
        }
    }
    return maxModul;
}

// --- GŁÓWNA ANALIZA ---
void uruchomEksperyment(int n, double rho_stopu, int wariant_x0) {
    Eigen::MatrixXd A = generujMacierzA(n);
    Eigen::VectorXd x_ref = generujWektorReferencyjny(n);
    Eigen::VectorXd b = A * x_ref; // b obliczone z x referencyjnego

    // Dobór wektora początkowego x_0
    Eigen::VectorXd x_0 = Eigen::VectorXd::Zero(n);
    if (wariant_x0 == 1) x_0 = Eigen::VectorXd::Constant(n, 100.0); // Dalekie przybliżenie

    //double promien = obliczPromienSpektralnyJacobiego(A);


    auto wynikPrzyrostowe = rozwiazJacobi(A, b, x_0, KryteriumStopu::Przyrostowe, rho_stopu);
    auto wynikResydualne = rozwiazJacobi(A, b, x_0, KryteriumStopu::Resydualne, rho_stopu);

    // Dokładność obliczeń (Norma różnicy x_obliczone i x_ref)
    double bladPrzyrostowe = (wynikPrzyrostowe.x - x_ref).lpNorm<Eigen::Infinity>();
    double bladResydualne = (wynikResydualne.x - x_ref).lpNorm<Eigen::Infinity>();

    // Wyświetlanie wyników w formie czytelnej tabeli
    std::cout << std::setw(5) << n
              << std::setw(10) << std::format("{:.0e}", rho_stopu)
              << std::setw(12) << (wariant_x0 == 0 ? "Zera" : "Stale(10)")
             // << std::setw(8) << promien << (promien < 1.0 ? " (OK)" : " (ERR)")
              << " | "
              << std::setw(15) << wynikPrzyrostowe.liczbaIteracji
              << std::setw(30) << wynikPrzyrostowe.czasMs
              << std::setw(12) << std::format("{:.3e}", bladPrzyrostowe)
              << " | "
              << std::setw(15) << wynikResydualne.liczbaIteracji
              << std::setw(30) << wynikResydualne.czasMs
              << std::setw(12) << std::format("{:.3e}", bladResydualne) << "\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "===============================================================================================\n";
    std::cout << "                                     RAPORT Z BADAN NUMERYCZNYCH                               \n";
    std::cout << "===============================================================================================\n";
    std::cout << "Norma uzywana do walidacji stopu oraz bledu: Norma Euklidesowa (L2)\n";
    std::cout << "-----------------------------------------------------------------------------------------------\n";
    std::cout << "  N   |  Rho    |    X0      |  Rad.Spec | Iter(P)  Czas(P)    Blad(P)   | Iter(R)  Czas(R)    Blad(R)   \n";
    std::cout << "-----------------------------------------------------------------------------------------------\n";

    // Testy dla różnych rozmiarów macierzy (N) oraz różnych dokładności (Rho)
    std::vector<int> rozmiary = {10,20, 30, 40, 50, 100, 400, 500};
    std::vector<double> tolerancje = {1e-4, 1e-8, 1e-12, 1e-16};

    for (int n : rozmiary) {
        for (double rho : tolerancje) {
            uruchomEksperyment(n, rho, 0); // wariant z x0 = wektor zerowy
            uruchomEksperyment(n, rho, 1); // wariant z x0 = wektor stałych 10
        }
        std::cout << "-----------------------------------------------------------------------------------------------\n";
    }

    return 0;
}