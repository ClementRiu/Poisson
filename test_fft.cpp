#include "fft.h"
#include <iostream>

const int W=8, H=2; // Dimensions du signal 2D
const int N=W*H;    // Dimensions du signal 1D

// Affichage d'un tableau de complexes.
void print(const std::complex<float> f[], int n) {
    for(int i=0; i<n; i++)
        std::cout << f[i] << " ";
    std::cout << std::endl;
}

// Initialisation du tableau f de taille n.
void init(std::complex<float> f[], int n) {
    for(int i=0; i<n; i++)
        f[i]=n-i;
}

// Test FFT. 
int main() {
    std::complex<float> f[N], g[N];

    init(f,N);
    print(f, N);

    // DFT
    for(int i=0; i<N; i++)
        g[i] = dft(f, N, i);
    print(g, N);

    std::cout << "-- 1D --" << std::endl;

    // FFT. Comparez avec g.
    fft(f, N);
    print(f, N);

    // IFFT. Comparez avec le f initial.
    ifft(f, N);
    print(f, N);

    std::cout << "-- 2D --" << std::endl;
    init(f, N);

    // FFT.
    fft2(f, W, H);
    print(f, N);

    // IFFT.
    ifft2(f, W, H);
    print(f, N);

    return 0;
}
