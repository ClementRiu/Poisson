#include "poisson.h"

// Selection a la souris d'un rectangle.
bool selectionRect(int &x1, int &y1, int &x2, int &y2, const Image<byte> &I) {
    Event e;
    do {
        getEvent(0, e);
        if (e.type == EVT_BUT_ON) {
            x1 = x2 = e.pix[0];
            y1 = y2 = e.pix[1];
            if (e.button == 3)
                return false;
        }
        if (e.type == EVT_MOTION) {
            x2 = e.pix[0];
            y2 = e.pix[1];
            display(I);
            drawRect(min(x1, x2), min(y1, y2), abs(x1 - x2), abs(y1 - y2),
                     RED);
        }
    } while (e.type != EVT_BUT_OFF || abs(x1 - x2) < 5 || abs(y1 - y2) < 5);
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    return true;
}

// Place interactivement la petite image fg dans l'image bg.
void cloneRect(int &xc, int &yc, const Image<byte> &bg, const Image<byte> &fg) {
    Event e;
    do {
        getEvent(0, e);
        if (e.type == EVT_BUT_ON || e.type == EVT_MOTION) {
            xc = e.pix[0];
            yc = e.pix[1];
            display(bg);
            display(fg, xc, yc);
        }
    } while (e.type != EVT_BUT_OFF);
}

// Mets dans Vx2, Vy2 le plus fort gradient.
void maxGradient(const Image<float> &Vx1, const Image<float> &Vy1,
                 Image<float> &Vx2, Image<float> &Vy2,
                 int x1, int y1, int x2, int y2, int xc, int yc) {
    for (int i = 0; i < x2 - x1; i++) {
        for (int j = 0; j < y2 - y1; j++) {
            if (pow(Vx1(x1 + i, y1 + j) + Vy1(x1 + i, y1 + j),2) > pow(Vx2(xc + i, yc + j) + Vy2(xc + i, yc + j),2)) {
                Vx2(xc + i, yc + j) = Vx1(x1 + i, y1 + j);
                Vy2(xc + i, yc + j) = Vy1(x1 + i, y1 + j);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    Image<byte> I1, I2;
    const char *fic1 = srcPath("bateau1.jpg");
    const char *fic2 = srcPath("bateau2.jpg");
    if (argc > 2) {
        fic1 = argv[1];
        fic2 = argv[2];
    }
    if (!load(I1, fic1) || !load(I2, fic2)) {
        cout << "Probleme dans le chargement d'images" << endl;
        return 1;
    }

    Window W1 = openWindow(I1.width(), I1.height());
    display(I1);
    Window W2 = openWindow(I2.width(), I2.height());
    setActiveWindow(W2);

    affiche(I2);

    Image<float> Vx1 = dx(I1),
                Vy1 = dy(I1),
                Vx2 = dx(I2),
                Vy2 = dy(I2);
    //gradient(I1, Vx1, Vy1);
    //gradient(I2, Vx2, Vy2);

    int x1, x2, y1, y2;
    int xc = 0;
    int yc = 0;

    cout << "Prêt à démarrer"<<endl;

    setActiveWindow(W1);
    selectionRect(x1, y1, x2, y2, I1);

    setActiveWindow(W2);
    getMouse(xc, yc);
    int w = x2 - x1;
    int h = y2 - y1;


    if (w + xc > I2.width()) {
        w -= xc;
    }

    if (h + yc > I2.height()) {
        h -= yc;
    }


    Image<float> Rec(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            Rec(i, j) = I1(i + x1, j + y1);
        }
    }

    cloneRect(xc, yc, I2, Rec);

    cout<<"..."<<endl;

    affiche(I2);

    click();

    cout<<"..."<<endl;

    maxGradient(Vx1, Vy1, Vx2, Vy2, x1, y1, x2, y2, xc, yc);

    int w2 = Vx2.width();
    int h2 = Vx2.height();

    int a = puis2(w2);
    int b = puis2(h2);

    Vx2 = agrandis(Vx2, a, b);
    Vy2 = agrandis(Vy2, a, b);

    Image<float> z = poisson(Vx2, Vy2);
    z.getSubImage(0, 0, w2, h2);
    affiche(z);

    click();

    endGraphics();
    return 0;
}
