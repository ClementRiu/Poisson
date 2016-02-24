#include "fft.h"
#include "assert.h"

// Discrete Fourier transform a l'index k du signal f de longueur n.
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
complex<float> dft(const complex<float> f[], int n, int k, float s) {
    complex<float> somme = 0;
    for (int i = 0; i < n; i++) {
        somme += f[i] * polar<float>(1.0f, float(s * 2 * i * k * M_PI / n));
    }

    return polar(sqrt(1 / float(n)), 0.0f) * somme;

}

// Fast Fourier transform du signal f(deb:pas:fin) (Matlab notation).
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
// Buffer est utilise comme tableau temporaire, sa longueur doit etre au moins
// celle de f.
void fft_main(complex<float> f[], int deb, int pas, int fin, float s,
              complex<float> buffer[]) {
    int n = (fin - deb) / pas + 1;
    if (n == 1) {
        return;
    }

    assert(n % 2 == 0);

    fft_main(f, deb, 2 * pas, fin - pas, -1.0f, buffer);
    fft_main(f, deb + pas, 2 * pas, fin, -1.0f, buffer);

    for (int i = 0; i < n; i++) {
        buffer[i] = f[deb + i * pas];
    }

    complex<float> t = 1;
    complex<float> w = polar(1.0f, float(s * 2 * M_PI / n));

    for (int i = 0; i < n / 2; i++) {
        f[deb + i * pas] = buffer[2 * i] + t * buffer[2 * i + 1];
        f[deb + (i + n / 2) * pas] = buffer[2 * i] - t * buffer[2 * i + 1];

        t *= w;
    }
}

// Divise tous les coefficients de f par la racine carree de sa longueur n.
void normalize(complex<float> f[], int n, float div) {
    for (int i = 0; i < n; i++)
        f[i] /= div;
}

// FFT du signal f de longueur n.
void fft(complex<float> f[], int len) {
    complex<float> *buffer = new complex<float>[len];

    fft_main(f, 0, 1, len - 1, -1.0f, buffer);
    normalize(f, len, sqrt(float(len)));

    delete[] buffer;
}

// FFT inverse du signal f de longueur n.
void ifft(complex<float> f[], int len) {
    complex<float> *buffer = new complex<float>[len];

    fft_main(f, 0, 1, len - 1, 1.0f, buffer);
    normalize(f, len, sqrt(float(len)));

    delete[] buffer;
}

// FFT du signal 2D f de dimension wxh.
void fft2(complex<float> f[], int w, int h) {
    complex<float> *buffer = new complex<float>[w * h];

    for (int i = 0; i < h; i++) {
        fft_main(f, i * w, 1, (1 + i) * w - 1, -1.0f, buffer);
    }
    for (int i = 0; i < w; i++) {
        fft_main(f, i, w, (h - 1) * w + i, -1.0f, buffer);
    }

    normalize(f, w * h, sqrt(float(w * h)));

    delete[] buffer;
}

// FFT inverse du signal 2D f de dimentsion wxh.
void ifft2(complex<float> f[], int w, int h) {
    complex<float> *buffer = new complex<float>[w * h];

    for (int i = 0; i < h; i++) {
        fft_main(f, i * w, 1, (1 + i) * w - 1, 1.0f, buffer);
    }
    for (int i = 0; i < w; i++) {
        fft_main(f, i, w, (h - 1) * w + i, 1.0f, buffer);
    }

    normalize(f, w * h, sqrt(float(w * h)));

    delete[] buffer;
}
