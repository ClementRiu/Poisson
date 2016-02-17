#include "fft.h"

// Discrete Fourier transform a l'index k du signal f de longueur n.
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
std::complex<float> dft(const std::complex<float> f[], int n, int k, float s) {
    return 0;
}

// Fast Fourier transform du signal f(deb:pas:fin) (Matlab notation).
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
// Buffer est utilise comme tableau temporaire, sa longueur doit etre au moins
// celle de f.
void fft_main(std::complex<float> f[], int deb, int pas, int fin, float s,
              std::complex<float> buffer[]) {
}

// Divise tous les coefficients de f par la racine carree de sa longueur n.
void normalize(std::complex<float> f[], int n, float div) {
    for(int i=0; i<n; i++)
        f[i] /= div;
}

// FFT du signal f de longueur n.
void fft(std::complex<float> f[], int n) {
}

// FFT inverse du signal f de longueur n.
void ifft(std::complex<float> f[], int n) {
}

// FFT du signal 2D f de dimension wxh.
void fft2(std::complex<float> f[], int w, int h) {
}

// FFT inverse du signal 2D f de dimentsion wxh.
void ifft2(std::complex<float> f[], int w, int h) {
}
