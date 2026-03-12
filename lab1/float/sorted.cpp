#include <iostream>
#include <iomanip>
#include "../Clock.cpp"

using namespace std;
void heapsort(float* arr, int n);
void heapify(float* arr, int n, int i);

int sorted() {
    // Ustawienie wypisywania pełnej precyzji
    cout << fixed << setprecision(10);
    float* valuesToSum = new float[1000001];
     for (int i=1;i<1000001;i++) {
         valuesToSum[i] = 1e-6f;
     }
    valuesToSum[0] = 1;


    const Timer t;
    heapsort(valuesToSum, 1000000);

    volatile float sum_ordered = 0;
    for (int i=0;i<1000001;i++) {
        sum_ordered += valuesToSum[i];
    }
    const double time_sorted = t.elapsed();
    cout << "Suma (sortowanie):" << sum_ordered << endl << "Czas (z sortowaniem):" << time_sorted << endl;
    delete [] valuesToSum;
    return 0;
}

void heapify(float* arr, int n, int i)
{
    int largest = i; // Initialize largest as root Since we are using 0 based indexing
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapsort(float* arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}