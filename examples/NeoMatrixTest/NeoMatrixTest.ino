#include <PICxel.h>
#include <NeoMatrix.h>

// 56 LEDs on pin 0.
// Must be running in GRB mode.
PICxel strip(56, 0, GRB);

// 56 LEDs can be arranged as 8x7, and wiring
// is easiest in Zig-Zag mode.
NeoMatrix tft(strip, 8, 7, NeoMatrix::ZIGZAG);

void setup() {
	tft.initializeDevice();
	tft.fillScreen(Color::Black);
}

void loop() {
	tft.setCursor(0, 0);
	tft.print(millis() / 1000);
	delay(100);
}
