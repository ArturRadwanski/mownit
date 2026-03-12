#include <iostream>
#include <iomanip>
#include "../Clock.cpp"

using namespace std;

int naive() {
    // Ustawienie wypisywania pełnej precyzji
    cout << fixed << setprecision(10);
    long double sum = 1;
    const Timer t;
    for (int i=0;i<1e6;i++) {
        sum += 1e-6;
    }

    const long double time_sorted = t.elapsed();

    cout << "Dodawanie \"naturalne\":" << sum << endl << "Czas:" << time_sorted << endl;

    return 0;
}

