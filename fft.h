#pragma once

#include <iostream>
#include <complex>
using namespace std;

complex<float> dft(const complex<float> f[], int n, int k,
                        float s=-1.0f);

void  fft(complex<float> f[], int n);
void ifft(complex<float> f[], int n);

void  fft2(complex<float> f[], int w, int h);
void ifft2(complex<float> f[], int w, int h);
