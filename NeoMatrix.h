#ifndef _NEOMATRIX_H
#define _NEOMATRIX_H

#include <Arduino.h>
#include <DisplayCore.h>
#include <PICxel.h>


class NeoMatrix : public DisplayCore {
    private:
        PICxel *_strip;
        int _width;
        int _height;
        uint8_t _mode;
        int _buffer;
        bool _inverted;

    public:
        NeoMatrix(PICxel &strip, int w, int h, uint8_t mode = LINEAR) : _strip(&strip), _width(w), _height(h), _mode(mode), _buffer(0), _inverted(false) {}
        NeoMatrix(PICxel *strip, int w, int h, uint8_t mode = LINEAR) : _strip(strip), _width(w), _height(h), _mode(mode), _buffer(0), _inverted(false) {}

        int getWidth() { return _width; }
        int getHeight() { return _height; }

        void setPixel(int x, int y, color_t color);
        void setRotation(int rotation);
        void initializeDevice();
        void displayOn();
        void displayOff();
        void invertDisplay(boolean i);
        void startBuffer();
        void endBuffer();

        static const uint8_t LINEAR = 0;
        static const uint8_t ZIGZAG = 1;
};

#endif
