#include "poisson.h"

// Selection a la souris d'un rectangle.
bool selectionRect(int& x1, int& y1, int& x2, int& y2, const Image<byte>& I) {
    Event e;
    do {
        getEvent(0, e);
        if(e.type==EVT_BUT_ON) {
            x1 = x2 = e.pix[0];
            y1 = y2 = e.pix[1];
            if(e.button==3)
                return false;
        }
        if(e.type==EVT_MOTION) {
            x2 = e.pix[0];
            y2 = e.pix[1];
            display(I);
            drawRect(std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2),
                     RED);
        }
    } while(e.type!=EVT_BUT_OFF || abs(x1-x2)<5 || abs(y1-y2)<5);
    if(x1>x2) std::swap(x1,x2);
    if(y1>y2) std::swap(y1,y2);
    return true;
}

// Place interactivement la petite image fg dans l'image bg.
void cloneRect(int& xc, int& yc, const Image<byte>& bg, const Image<byte>& fg) {
    Event e;
    do {
        getEvent(0, e);
        if(e.type==EVT_BUT_ON || e.type==EVT_MOTION) {
            xc = e.pix[0];
            yc = e.pix[1];
            display(bg);
            display(fg, xc, yc);
        }
    } while(e.type != EVT_BUT_OFF);
}

// Mets dans Vx2, Vy2 le plus fort gradient.
void maxGradient(const Image<float>& Vx1, const Image<float>& Vy1,
                 Image<float>& Vx2, Image<float>& Vy2,
                 int x1, int y1, int x2, int y2, int xc, int yc) {
    // A completer
}

int main(int argc, char* argv[]) {
    Image<byte> I1, I2;
    const char* fic1 = srcPath("bateau1.jpg");
    const char* fic2 = srcPath("bateau2.jpg");
    if(argc>2) {
        fic1 = argv[1];
        fic2 = argv[2];
    }
    if(! load(I1, fic1) || ! load(I2, fic2)) {
        std::cout << "Probleme dans le chargement d'images" << std::endl;
        return 1;
    }

    Window W1 = openWindow(I1.width(), I1.height());
    display(I1);
    Window W2 = openWindow(I2.width(), I2.height());
    setActiveWindow(W2);
    I2 = affichable(I2);
    display(I2);

    // A completer

    endGraphics();
    return 0;
}
