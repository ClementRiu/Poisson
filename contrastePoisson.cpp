#include "poisson.h"

const byte OBSCUR = 50; // Seuil d'intensite des pixels dont on change le gradient
const float FACTEUR = 3.0f; // Facteur de multiplication du gradient

// Rehausse le gradient des pixels sombres, et montre en rouge ces pixels.
void masque(const Image<float> &I, Image<float> &Vx, Image<float> &Vy) {
    for (int i=0; i<I.width() ; i++){
        for (int j=0 ; j<I.height() ; j++){
            if (I(i,j)<OBSCUR){
                Vx(i,j)*=FACTEUR;
                Vy(i,j)*=FACTEUR;
                drawPoint(i,j,RED);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    Image<byte> I;
    Image<float> Vx, Vy;
    if (!load(I, argc > 1 ? argv[1] : srcPath("bateau2.jpg"))) {
        cout << "Echec de lecture d'image" << endl;
        return 1;
    }

    openWindow(I.width(), I.height());
    display(I);
    click();
    cout << "Contraste simple" << endl;
    affiche(I);
    gradient(I, Vx, Vy);
    click();
    affiche(Vx);
    click();
    affiche(Vy);


    click();


    Image<float> F = dx(I);

    affiche(F);

    click();

    Image<float> U= dy(I);
    affiche(U);
    click();

    masque(I,F,U);

    Image<float> z = poisson(F,U);
    affiche(z);

    endGraphics();
    return 0;
}
