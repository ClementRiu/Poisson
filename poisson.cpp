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

Image<float> agrandis(const Image<float> &I,
                                int w, int h) {
    Image<float> I2(w, h);
    I2.fill(0.0f);
    for (int i = 0; i < I.height(); i++)
        for (int j = 0; j < I.width(); j++)
            I2(j, i) = I(j, i);
    return I2;
}


/*
template <typename T>
Image<T> agrandis(const Image <T> &I, int w, int h){
    Image<T> I2(w, h);
    I2.fill(0.0f);
    for (int i = 0; i < I.height(); i++)
        for (int j = 0; j < I.width(); j++)
            I2(j, i) = I(j, i);
    return I2;
}
 */

// Gradient de l'image I par differences finies.
void gradient(const Image<float> &I, Image<float> &Vx, Image<float> &Vy) {
    Vx = Image<float>(I.width(), I.height());
    Vy = Image<float>(I.width(), I.height());
    FVector<float, 2> T;

    for (int i = 0; i < I.width(); i++) {
        for (int j = 0; j < I.height(); j++) {
            T = gradient(I, Coords<2>(i, j));
            Vx(i, j) = T[0];
            Vy(i, j) = T[1];
        }
    }
}

// Calcul en Fourier de la derivee suivant x.
void Fourier_dx(Image<complex<float> > &F) {
    fft2(F.data(), F.width(), F.height());

    complex<float> u = polar<float>(1.0f, float(M_PI / 2));

    for (int i = 0; i < F.width() / 2; i++) {
        for (int j = 0; j < F.height(); j++) {
            F(i, j) *= 2 * float(M_PI) * i * u * (1 / float(F.width()));
        }
    }

    for (int j = 0; j < F.height(); j++) {
        F(F.width() / 2, j) = 0;
    }

    for (int i = F.width() / 2 + 1; i < F.width(); i++) {
        for (int j = 0; j < F.height(); j++) {
            F(i, j) *= 2 * float(M_PI) * (i - F.width()) * u * (1 / float(F.width()));
        }
    }
}

// Derivee suivant x par DFT.
Image<float> dx(Image<complex<float> > F) {
    F = F.clone();

    int w = F.width();
    int h = F.height();

    int a = puis2(F.width());
    int b = puis2(F.height());

    F = agrandis(F, a, b);

    Fourier_dx(F);

    ifft2(F.data(), F.width(), F.height());

    return realImage(F.getSubImage(0,0,w,h));
}

// Calcul en Fourier de la derivee suivant y.
void Fourier_dy(Image<complex<float> > &F) {
    fft2(F.data(), F.width(), F.height());

    complex<float> u = polar<float>(1.0f, float(M_PI / 2));

    for (int i = 0; i < F.height() / 2; i++) {
        for (int j = 0; j < F.width(); j++) {
            F(j, i)*= 2 * float(M_PI) * i * u * (1 / float(F.height()));
        }
    }

    for (int j = 0; j < F.height(); j++) {
        F(j, F.height() / 2) = 0;
    }

    for (int i = F.height() / 2 + 1; i < F.height(); i++) {
        for (int j = 0; j < F.width(); j++) {
            F(j, i) *= 2 * float(M_PI) * (i - F.height()) * u * (1 / float(F.height()));
        }
    }
}

// Derivee suivant y par DFT.
Image<float> dy(Image<complex<float> > F) {
    F = F.clone();

    int w = F.width();
    int h = F.height();

    int a = puis2(F.width());
    int b = puis2(F.height());


    F = agrandis(F, a, b);

    Fourier_dy(F);

    ifft2(F.data(), F.width(), F.height());

    F.getSubImage(0, 0, w, h);

    return realImage(F.getSubImage(0, 0, w, h));
}

// Resouds l'equation de Poisson.
Image<float> poisson(Image<complex<float> > Vx,
                     Image<complex<float> > Vy) {
    Image<complex<float> > u(Vx.width(), Vx.height());

    complex<float> z = polar<float>(1.0f, float(M_PI / 2));

    fft2(Vx.data(), Vx.width(), Vx.height());
    fft2(Vy.data(), Vy.width(), Vy.height());


    for (int i = 0; i < u.width(); i++) {
        for (int j = 0; j < u.height(); j++) {
            if (i == 0 && j == 0) {
                u(i, j) = 0;
            }

            if (i < u.width() / 2 && j < u.height() / 2 && (i != 0 && j != 0)) {
                u(i, j) = ((2 * float(M_PI) * i * z / float(u.width())) * Vx(i, j) +
                           (2 * float(M_PI) * j * z / float(u.height())) * Vy(i, j))
                          / (pow(2 * float(M_PI) * i * z / float(u.width()), 2) +
                             pow(2 * float(M_PI) * j * z / float(u.height()), 2));
            }

            if (i < u.width() / 2 && j >= u.height() / 2) {
                u(i, j) = ((2 * float(M_PI) * i * z / float(u.width())) * Vx(i, j) +
                           (2 * float(M_PI) * (j - u.width()) * z / float(u.height())) * Vy(i, j))
                          / (pow(2 * float(M_PI) * i * z / float(u.width()), 2) +
                             pow(2 * float(M_PI) * (j - u.width()) * z / float(u.height()), 2));
            }

            if (i >= u.width() / 2 && j < u.height() / 2) {
                u(i, j) = ((2 * float(M_PI) * (i - u.width()) * z / float(u.width())) * Vx(i, j) +
                           (2 * float(M_PI) * j * z / float(u.height())) * Vy(i, j))
                          / (pow(2 * float(M_PI) * (i - u.width()) * z / float(u.width()), 2) +
                             pow(2 * float(M_PI) * j * z / float(u.height()), 2));
            }

            if (i >= u.width() / 2 && j >= u.height() / 2) {
                u(i, j) = ((2 * float(M_PI) * (i - u.width()) * z / float(u.width())) * Vx(i, j) +
                           (2 * float(M_PI) * (j - u.height()) * z / float(u.height())) * Vy(i, j))
                          / (pow(2 * float(M_PI) * (i - u.width()) * z / float(u.width()), 2) +
                             pow(2 * float(M_PI) * (j - u.height()) * z / float(u.height()), 2));
            }
        }
    }
    ifft2(u.data(), u.width(), u.height());

    return realImage(u);
}
