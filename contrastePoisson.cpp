#include "poisson.h"

const byte OBSCUR = 50; // Seuil d'intensite des pixels dont on change le gradient
const float FACTEUR = 3.0f; // Facteur de multiplication du gradient

// Rehausse le gradient des pixels sombres, et montre en rouge ces pixels.
void masque(const Image<float> &I, Image<float> &Vx, Image<float> &Vy) {
    // A completer
}

int main(int argc, char *argv[]) {
    Image<byte> I;
    if (!load(I, argc > 1 ? argv[1] : srcPath("salon.png"))) {
        cout << "Echec de lecture d'image" << endl;
        return 1;
    }

    openWindow(I.width(), I.height());
    display(I);
    click();
    cout << "Contraste simple" << endl;
    affiche(I);
    click();

    // A completer

    endGraphics();
    return 0;
}
