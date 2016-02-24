#include "poisson.h"
#include "fft.h"
#include <algorithm>

const float POURCENT = 0.5f;

// Fonction affine amenant les min et max de F (ignorant les POURCENT valeurs
// extremes de chaque cote) a 0 et 255.
void affineContraste(Image<float> F, float &a, float &b) {
    F = F.clone();
    sort(F.begin(), F.end());
    int p = (int) (F.totalSize() * POURCENT / 100);
    float min = F[p];
    float max = F[F.totalSize() - 1 - p];
    a = (min < max) ? 255.0f / (max - min) : 0;
    b = (min < max) ? -a * min : 255.0f / 2;
}

// Renvoie une image affichable.
Image<byte> affichable(const Image<float> &F) {
    float a, b;
    affineContraste(F, a, b);
    Image<byte> I(F.width(), F.height());
    for (int i = 0; i < I.height(); i++)
        for (int j = 0; j < I.width(); j++) {
            float f = a * F(j, i) + b + 0.5f;
            if (f < 0) f = 0;
            if (f > 255) f = 255;
            I(j, i) = (byte) f;
        }
    return I;
}

// Affichage d'une image avec intensites reelles.
void affiche(const Image<float> &F) {
    display(affichable(F));
}

// Prend la partie reelle de chaque pixel d'une image complexe.
Image<float> realImage(const Image<complex<float> > &F) {
    const int w = F.width(), h = F.height();
    Image<float> I(w, h);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            I(j, i) = F(j, i).real();
    return I;
}

// Puissance de 2 immediatement superieure a i-1.
int puis2(int i) {
    int j = 1;
    while (j < i)
        j *= 2;
    return j;
}

// Genere une image plus grande en rajoutant des 0.
Image<complex<float> > agrandis(const Image<complex<float> > &I,
                                int w, int h) {
    Image<complex<float> > I2(w, h);
    I2.fill(0.0f);
    for (int i = 0; i < I.height(); i++)
        for (int j = 0; j < I.width(); j++)
            I2(j, i) = I(j, i);
    return I2;
}

// Gradient de l'image I par differences finies.
void gradient(const Image<float> &I, Image<float> &Vx, Image<float> &Vy) {
    Vx = Image<float>(I.width(), I.height());
    Vy = Image<float>(I.width(), I.height());
    // A completer
}

// Calcul en Fourier de la derivee suivant x.
void Fourier_dx(Image<complex<float> > &F) {
}

// Derivee suivant x par DFT.
Image<float> dx(Image<complex<float> > F) {
    // A completer
    return realImage(F);
}

// Calcul en Fourier de la derivee suivant y.
void Fourier_dy(Image<complex<float> > &F) {
}

// Derivee suivant y par DFT.
Image<float> dy(Image<complex<float> > F) {
    // A completer
    return realImage(F);
}

// Resouds l'equation de Poisson.
Image<float> poisson(Image<complex<float> > Vx,
                     Image<complex<float> > Vy) {
    Image<complex<float> > u(Vx.width(), Vx.height());
    // A completer
    return realImage(u);
}
