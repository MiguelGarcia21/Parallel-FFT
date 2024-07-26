// ParallelFFT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <complex>
#include <chrono>
#include <cmath>
#include <omp.h>

using namespace std;
using namespace std::chrono;

void fft(vector<complex<double>>& x) {
    const int N = x.size();
    if (N == 1) return;

    vector<complex<double>> even(N / 2);
    vector<complex<double>> odd(N / 2);

#pragma omp parallel for
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

#pragma omp parallel sections
    {
#pragma omp section
        fft(even);

#pragma omp section
        fft(odd);
    }

#pragma omp parallel for
    for (int k = 0; k < N / 2; k++) {
        complex<double> t = std::exp(std::complex<double>(0, -2 * M_PI * k / N)) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

int main() {
    const int size = 262144;
    vector<complex<double>> data(size);

    // Initialize input data with fixed values
    for (int i = 0; i < size; i++) {
        data[i] = complex<double>(cos(2 * M_PI * i / size), sin(2 * M_PI * i / size));
    }

    // Set the number of threads
    omp_set_num_threads(8);

    auto start = high_resolution_clock::now();
    fft(data);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "FFT computation time: " << duration.count() << " milliseconds" << endl;

    // Print the first few elements of the result
    cout << "First few elements of the result: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
