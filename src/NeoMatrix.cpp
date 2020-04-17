#include <NeoMatrix.h>

void NeoMatrix::setPixel(int x, int y, color_t color) {
    uint8_t red = color >> 11;
    uint8_t green = color >> 5 & 0b111111;
    uint8_t blue = color & 0b11111;

    setPixel(x, y, red, green, blue);
}

void NeoMatrix::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    int pixNumber = 0;

    if (_xflip) x = getWidth() - x - 1;
    if (_yflip) y = getHeight() - y - 1;

    if (_rot) {
        int z = x;
        x = y;
        y = z;
    }

    if (x >= _width) return;
    if (x < 0) return;
    if (y >= _height) return;
    if (y < 0) return;

    if (_mode == LINEAR) {
        pixNumber = x + (y * _width);
    } else if (_mode == ZIGZAG) {
        if (y & 1) { // Odd row - reversed
            pixNumber = y * _width + (_width - x - 1);
        } else {
            pixNumber = y * _width + x;
        }
    }

    if (_inverted) {
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
    }

    _strip->GRBsetLEDColor(pixNumber, green, red, blue);
    if (_buffer <= 0) {
        _strip->refreshLEDs();
    }
}


void NeoMatrix::setRotation(int rotation) {
}

void NeoMatrix::initializeDevice() {
    _strip->begin();
}

void NeoMatrix::displayOn() {
}

void NeoMatrix::displayOff() {
}

void NeoMatrix::invertDisplay(bool i) {
    _inverted = i;
}

void NeoMatrix::startBuffer() {
    _buffer++;
}

void NeoMatrix::endBuffer() {
    _buffer--;
    if (_buffer <= 0) {
        _buffer = 0;
        _strip->refreshLEDs();
    }
}

int NeoMatrix::getWidth() {
    return _rot ? _height : _width;
}

int NeoMatrix::getHeight() {
    return _rot ? _width : _height;
}


