#include "fft.h"

// Discrete Fourier transform a l'index k du signal f de longueur n.
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
complex<float> dft(const complex<float> f[], int n, int k, float s) {
    complex<float> somme=0;
    for (int i=0; i<n ; i++){
        somme+=f[i]*polar<float>(1.0f,float(s*2*i*k*M_PI/n));
    }
    return somme*polar(float(sqrt(1/n)),0.0f);
}

// Fast Fourier transform du signal f(deb:pas:fin) (Matlab notation).
// s=-1 pour DFT directe, s=+1 pour DFT inverse.
// Buffer est utilise comme tableau temporaire, sa longueur doit etre au moins
// celle de f.
void fft_main(complex<float> f[], int deb, int pas, int fin, float s,
              complex<float> buffer[]) {
    int n= (fin-deb)/pas;
    if (n==1){

    }
    for (int i=deb; i<fin;i+=pas){
    }
}

// Divise tous les coefficients de f par la racine carree de sa longueur n.
void normalize(complex<float> f[], int n, float div) {
    for(int i=0; i<n; i++)
        f[i] /= div;
}

// FFT du signal f de longueur n.
void fft(complex<float> f[], int n) {
    complex<float>* buffer = new complex<float>[n];/*
    for (int i=0; i<n; i++){
        buffer[i]=f[i];
    }*/
    fft_main(f,0,2,n,1.0f,buffer);
    fft_main(f,1,2,n+1,1.0f,buffer);
    normalize(f,n,sqrt(n));
    delete[]buffer;
}

// FFT inverse du signal f de longueur n.
void ifft(complex<float> f[], int n) {
    complex<float>* buffer = new complex<float>[n];
    for (int i=0; i<n; i++){
        buffer[i]=f[i];
    }
    fft_main(f,0,2,n,-1.0f,buffer);
    fft_main(f,1,2,n+1,-1.0f,buffer);
    normalize(f,n,sqrt(n));
    delete[]buffer;
}

// FFT du signal 2D f de dimension wxh.
void fft2(complex<float> f[], int w, int h) {
}

// FFT inverse du signal 2D f de dimentsion wxh.
void ifft2(complex<float> f[], int w, int h) {
}
