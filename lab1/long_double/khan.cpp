#include <iostream>
#include <iomanip>
#include "../Clock.cpp"

using namespace std;

int khan() {
    // Ustawienie wypisywania pełnej precyzji
    cout << fixed << setprecision(10);
    long double* valuesToSum = new long double[1000001];
     for (int i=1;i<1000001;i++) {
         valuesToSum[i] = 1e-6;
     }
    valuesToSum[0] = 1;


    long double sum = 0;
    long double c = 0;
    Timer t;
    for (int i=0;i<1000001;i++) {
        long double y = valuesToSum[i] - c;
        long double t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    long double time_sorted = t.elapsed();
    cout << "Suma khan:" << sum << endl << "Czas:" << time_sorted << endl;
    delete [] valuesToSum;
    return 0;
}

