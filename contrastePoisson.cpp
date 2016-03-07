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
    if (!load(I, argc > 1 ? argv[1] : srcPath("salon.png"))) {
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
    cout << "Dérivée selon x par la fonction gradient" <<endl;
    affiche(Vx);
    click();
    cout << "Dérivée selon y par la fonction gradient" <<endl;
    affiche(Vy);

    click();

    Image<float> F = dx(I);

    cout << "Dérivée selon x par la fonction dx" <<endl;

    affiche(F);

    click();

    Image<float> U= dy(I);
    cout << "Dérivée selon y par la fonction dy" <<endl;

    affiche(U);

    click();

    masque(I,F,U);

    Image<float> z = poisson(F,U);
    cout << "Image reconstruite par poisson" <<endl;

    affiche(z);

    endGraphics();
    return 0;
}
