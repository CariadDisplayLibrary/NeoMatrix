#include <PICxel.h>
#include <NeoMatrix.h>

PICxel strip(60, 0, GRB);
NeoMatrix tft(strip, 8, 7);

USBFS usbDevice;
USBManager USB(usbDevice, 0xf055, 0x1234);
CDCACM uSerial;

void setup() {
	USB.addDevice(uSerial);
	USB.begin();
	strip.begin();

}

void loop() {
    for (int m = 59; m >= 0; m--) {
        for (int s = 0; s < m; s++) {
            strip.GRBsetLEDColor(s, 0, 0, 255);
            strip.refreshLEDs();
            delay(10);
            strip.GRBsetLEDColor(s, 0, 0, 0);
        }
        strip.GRBsetLEDColor(m, 0, 255, 0);
    }
    strip.refreshLEDs();

    delay(1000);

    for (int c = 255; c > 0; c--) {
        for (int i = 0; i < 60; i++) {
            strip.GRBsetLEDColor(i, c, 0, 0);
        }
        strip.refreshLEDs();
        delay(10);
    }
    delay(2000);
}
