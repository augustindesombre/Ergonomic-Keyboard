#ifndef SCREEN_H
#define SCREEN_H

#include <SPI.h>
#include <Wire.h>
#include <U8x8lib.h>
#include "TableOfCharacters.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Screen
{
private:
    U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8;
    int mode;
    String rightContent;
    String suggestion = "coming soon";
    bool on;
    bool mouse;
    int cmouse;
    int rmouse;
    int oldLPos;
    int oldRPos;

public:
    Screen();
    void begin();
    void swipe();
    void pre();
    void onOff();

    void changeSuggestion(String suggestion);
    void debug(int show);

    // Mouse mode
    void mouseMode();
    void updateMouse(float x, float y);

    // Keyboard mode
    void typeMode(int controllerState);
    void updateType(TableOfCharacters *toc, int controllerState, int lPos);

    // for test purposes
    void draw_bar(uint8_t c, uint8_t is_inverse);
    void draw_ascii_row(uint8_t r, int start);
    void loop(TableOfCharacters *toc);
};

#endif