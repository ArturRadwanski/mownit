#include <iostream>
#include <iomanip>
#include "Clock.cpp"

using namespace std;

int khan() {
    // Ustawienie wypisywania pełnej precyzji
    cout << fixed << setprecision(10);
    float* valuesToSum = new float[1000001];
     for (int i=1;i<1000001;i++) {
         valuesToSum[i] = 1e-6;
     }
    valuesToSum[0] = 1;


    float sum = 0;
    float c = 0;
    Timer t;
    for (int i=0;i<1000001;i++) {
        float y = valuesToSum[i] - c;
        float t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    double time_sorted = t.elapsed();
    cout << "Suma khan:" << sum << endl << "Czas:" << time_sorted << endl;
    free(valuesToSum);
    return 0;
}

