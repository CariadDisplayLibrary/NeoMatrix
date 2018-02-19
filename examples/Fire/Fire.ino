#include <PICxel.h>
#include <NeoMatrix.h>

const int w = 16;
const int h = 12;
uint16_t fire[h][w];

PICxel strip(w *h, 0, GRB);
NeoMatrix tft(strip, w, h, NeoMatrix::ZIGZAG);

void setup() {
	tft.initializeDevice();
	tft.fillScreen(Color::Black);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			fire[y][x] = 0;
		}
	}

	for (int x = 0; x < w; x++) {
		fire[h - 1][x] = rand() & 0x3FF;
	}
}

void loop() {
    static uint32_t ts = millis();

    if (millis() - ts > 100) {
        ts = millis();
		for (int x = 0; x < w; x++) {
			fire[h - 1][x] = rand() & 0x3FF;
		}
	}

	for (int y = 0; y < h - 1; y++) {
		for (int x = 0; x < w; x++) {
			float v =
			    fire[(y + 1) % h][(x - 1 + w) % w] +
			    fire[(y + 1) % h][x] +
			    fire[(y + 1) % h][(x + 1 + w) % w] +
			    fire[(y + 2) % h][x];
			v /= 7.5;
			fire[y][x] = (int16_t)v;
		}
	}

	tft.startBuffer();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (fire[y][x] < 256) {
				tft.setPixel(x, y, fire[y][x], 0, 0);
			} else {
				tft.setPixel(x, y, 255, fire[y][x] - 256, 0);
			}
		}
	}

	tft.endBuffer();
	delay(50);
}

