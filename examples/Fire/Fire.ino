#include <PICxel.h>
#include <NeoMatrix.h>

const int w = 16;
const int h = 13;
uint8_t fire[h][w];

PICxel strip(w*(h-1), 0, GRB);
NeoMatrix tft(strip, w, h-1, NeoMatrix::ZIGZAG);

void setup() {
	tft.initializeDevice();
	tft.fillScreen(Color::Black);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            fire[y][x] = 0;
        }
    }

}

void loop() {

    for (int x = 0; x < w; x++) {
        fire[h-1][x] = rand() & 0xFF;    
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float v = 
                fire[(y + 1) % h][(x - 1 + w) % w] +
                fire[(y + 1) % h][x] +
                fire[(y + 1) % h][(x + 1 + w) % w] +
                fire[(y + 2) % h][x];
            v /= 5.5;
            fire[y][x] = (int8_t)v;
        }
    }

    tft.startBuffer();

    for (int y = 0; y < h-1; y++) {
        for (int x = 0; x < w; x++) {
            tft.setPixel(x, y, fire[y][x], 0, 0);
        }
    }

    tft.endBuffer();

    delay(100);
}
