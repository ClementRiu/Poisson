#include "fft.h"
#include <iostream>

const int W = 8, H = 2; // Dimensions du signal 2D
const int N = W * H;    // Dimensions du signal 1D

// Affichage d'un tableau de complexes.
void print(const complex<float> f[], int n) {
    for (int i = 0; i < n; i++)
        cout << f[i] << " ";
    cout << endl;
}

// Initialisation du tableau f de taille n.
void init(complex<float> f[], int n) {
    for (int i = 0; i < n; i++)
        f[i] = n - i;
}

// Test FFT. 
int main() {
    complex<float> f[N], g[N];

    init(f, N);
    print(f, N);

    // DFT

    for (int i = 0; i < N; i++) {
        g[i] = dft(f, N, i);
    }
    cout << "Résultat de la DFT" << endl;
    print(g, N);

    cout << "-- 1D --" << endl;

    // FFT.
    fft(f, N);
    print(f, N);

    // IFFT.
    ifft(f, N);
    print(f, N);


    cout << "-- 2D --" << endl;
    init(f, N);

    // FFT.
    fft2(f, W, H);
    print(f, N);

    // IFFT.
    ifft2(f, W, H);
    print(f, N);

    return 0;
}
