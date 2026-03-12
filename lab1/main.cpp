#include <iostream>
#include <iomanip>
#include "Clock.cpp"

using namespace std;
float khan_algorithm(const float inputs[1000001]);
void quicksort(float arr[1000001], int low = 0, int high = 1000000);
float partition(float arr[1000001], int low, int high);

int main() {
    // Ustawienie wypisywania pełnej precyzji
    cout << fixed << setprecision(10);
    float valuesToSum[1000001];
     for (int i=1;i<1000001;i++) {
         valuesToSum[i] = 1e-6;
     }
    valuesToSum[0] = 1;
    Timer t;
    float sum_khan = khan_algorithm(valuesToSum);
    double time = t.elapsed();

    t.reset();
    float sum = 0;
    for (int i=0;i<1000001;i++) {
        sum += valuesToSum[i];
    }
    double time_naive = t.elapsed();
    t.reset();
    quicksort(valuesToSum, 0, 1000001);

    float sum_ordered;
    for (int i=0;i<1000001;i++) {
        sum_ordered += valuesToSum[i];
    }
    double time_sorted = t.elapsed();
    cout << sum_khan << endl << time << endl << sum << endl << time_naive << endl << sum_ordered << endl << time_sorted;

    return 0;
}

float khan_algorithm(const float inputs[1000001]) {
    float sum = 0;
    float c = 0;
    for (int i=0;i<1000001;i++) {
        float y = inputs[i] - c;
        float t = sum + y;
        c = t - sum - y;
        sum = t;
    }
    return sum;
}

float partition(float arr[1000001], int low, int high) {

    // choose the pivot
    int pivot = arr[high];

    // undex of smaller element and indicates
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// the QuickSort function implementation
void quicksort(float arr[1000001], int low, int high){

    if (low < high) {

        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}