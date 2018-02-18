#include <PICxel.h>
#include <NeoMatrix.h>
#include <Topaz.h>

const char *fullMSG = "Don't forget to LIKE and SUBSCRIBE if you enjoyed this video.";

// Must be running in GRB mode.
PICxel strip(16*12, 0, GRB);
NeoMatrix tft(strip, 16, 12, NeoMatrix::ZIGZAG);

void setup() {
	tft.initializeDevice();
	tft.fillScreen(Color::Black);
    tft.setFont(Fonts::Topaz);
    tft.setTextWrap(false);
}

void loop() {
    int sw = tft.stringWidth(fullMSG);
    for (int x = 16; x > 0 - sw; x--) {
        tft.setCursor(x, 2);
        tft.setTextColor(Color::Green);
        tft.print("Don't forget to ");
        tft.setTextColor(Color::Red);
        tft.print("LIKE");
        tft.setTextColor(Color::Green);
        tft.print(" and ");
        tft.setTextColor(Color::Blue);
        tft.print("SUBSCRIBE");
        tft.setTextColor(Color::Green);
        tft.print(" if you enjoyed this video.");
        delay(50);
    }
}
