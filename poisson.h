#pragma once

#include <complex>
#include <Imagine/Images.h>
using namespace Imagine;

Image<byte> affichable(const Image<float>& F);
void affiche(const Image<float>& F);

void gradient(const Image<float>& I, Image<float>& Vx, Image<float>& Vy);
Image<float> dx(Image< std::complex<float> > F);
Image<float> dy(Image< std::complex<float> > F);

Image<float> poisson(Image< std::complex<float> > Vx,
                     Image< std::complex<float> > Vy);
