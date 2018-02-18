#include <PICxel.h>
#include <NeoMatrix.h>
#include <Topaz.h>

#define DEPTH 255

PICxel strip(16*12, 0, GRB);
NeoMatrix tft(strip, 16, 12, NeoMatrix::ZIGZAG);

struct dot {
    double x;
    double y;
    double dx;
    double dy;
};

struct dot dots[3];

void setup() {
	tft.initializeDevice();
	tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Topaz);
    tft.setTextWrap(false);

    for (int i = 0; i < 3; i++) {
        dots[i].x = rand() % 14 + 1;
        dots[i].y = rand() % 9 + 1;
        dots[i].dx = rand() & 1 ? 0.05 : -0.05;
        dots[i].dy = rand() & 1 ? 0.05 : -0.05;
    }
}

void loop() {

    tft.startBuffer();

    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 16; x++) {
            double dx0 = abs(x - dots[0].x);
            double dy0 = abs(y - dots[0].y);
            double d0 = 1+sqrt(dx0*dx0 + dy0*dy0);
            int r = DEPTH * (1.0/(d0*d0));
            if (r > DEPTH) r = DEPTH;
            
            double dx1 = abs(x - dots[1].x);
            double dy1 = abs(y - dots[1].y);
            double d1 = 1+sqrt(dx1*dx1 + dy1*dy1);
            int g = DEPTH * (1.0/(d1*d1));
            if (g > DEPTH) g = DEPTH;

            double dx2 = abs(x - dots[2].x);
            double dy2 = abs(y - dots[2].y);
            double d2 = 1+sqrt(dx2*dx2 + dy2*dy2);
            int b = DEPTH * (1.0/(d2*d2));
            if (b > DEPTH) b = DEPTH;
            
            tft.setPixel(x, y, rgb(r, g, b));
        }
    }

    tft.endBuffer();

    for (int i = 0; i < 3; i++) {
        dots[i].x += dots[i].dx;
        dots[i].y += dots[i].dy;

        if ((dots[i].x <= 0) || (dots[i].x >= 15)) dots[i].dx = -dots[i].dx;
        if ((dots[i].y <= 0) || (dots[i].y >= 11)) dots[i].dy = -dots[i].dy;
    } 

//    delay(10);
}
