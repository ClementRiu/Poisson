#pragma once

#include <complex>

std::complex<float> dft(const std::complex<float> f[], int n, int k,
                        float s=-1.0f);

void  fft(std::complex<float> f[], int n);
void ifft(std::complex<float> f[], int n);

void  fft2(std::complex<float> f[], int w, int h);
void ifft2(std::complex<float> f[], int w, int h);
