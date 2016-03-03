#pragma once

#include <complex>
#include <Imagine/Images.h>
#include <iostream>

using namespace std;
using namespace Imagine;

Image<byte> affichable(const Image<float> &F);

void affiche(const Image<float> &F);

void gradient(const Image<float> &I, Image<float> &Vx, Image<float> &Vy);

Image<float> dx(Image<complex<float> > F);

Image<float> dy(Image<complex<float> > F);

Image<float> poisson(Image<complex<float> > Vx,
                     Image<complex<float> > Vy);