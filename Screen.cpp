#include "Screen.h"
#include <U8x8lib.h>
#include <Arduino.h>

Screen::Screen() : u8x8(/* reset=*/U8X8_PIN_NONE)
{
}

void Screen::begin()
{
    u8x8.begin();
    swipe();
    on = true;
}

void Screen::swipe()
{
    pre();
    uint8_t c;
    draw_bar(0, 1);
    for (c = 1; c < u8x8.getCols(); c++)
    {
        draw_bar(c, 1);
        draw_bar(c - 1, 0);
        delay(50);
    }
    draw_bar(u8x8.getCols() - 1, 0);
    draw_bar(u8x8.getCols() - 1, 1);
    for (c = u8x8.getCols() - 1; c > 0; c--)
    {
        draw_bar(c - 1, 1);
        draw_bar(c, 0);
        delay(50);
    }
    draw_bar(0, 0);
}

void Screen::pre()
{
    u8x8.clear();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
    u8x8.noInverse();
    u8x8.setCursor(0, 1);
}

void Screen::onOff()
{
    swipe();
    on = !on;
    if (on)
    {
        mouseMode();
    }
}

void Screen::mouseMode()
{
    mouse = true;
    pre();
    u8x8.inverse();
    u8x8.draw2x2String(0, 0, "S");
    u8x8.noInverse();
    u8x8.drawUTF8(8, 0, "|");
    u8x8.drawUTF8(8, 7, "|");
    u8x8.draw2x2UTF8(1, 3, "-");
    u8x8.draw2x2UTF8(14, 3, "-");
    cmouse = 7;
    rmouse = 2;
}

void Screen::updateMouse(float x, float y)
{
    if (on)
    {
        if (!mouse)
        {
            mouseMode();
        }
        int oldc = cmouse;
        int oldr = rmouse;
        cmouse = 8 + int(5 * x);
        rmouse = 3 + int(2 * y);
        u8x8.drawUTF8(cmouse, rmouse, ".");
        if (oldc != cmouse || oldr != rmouse)
        {
            u8x8.drawUTF8(oldc, oldr, " ");
        }
    }
}

void Screen::typeMode(int controllerState)
{
    mouse = false;
    pre();
    u8x8.inverse();
    switch (controllerState)
    {
    case (0):
        u8x8.draw2x2String(0, 0, "a");
        break;
    case (1):
        u8x8.draw2x2String(0, 0, "A");
        break;
    case (2):
        u8x8.draw2x2String(0, 0, "1");
        break;
    }
    mode = controllerState;
    u8x8.noInverse();
}

void Screen::updateType(TableOfCharacters *toc, int controllerState, int lPos)
{
    if (on)
    {
        bool update = false;
        if (mouse || mode != controllerState)
        {
            typeMode(controllerState);
            update = true;
        }
        if (oldLPos != lPos || update)
        {
            if (oldLPos == 7)
            {
                u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
                u8x8.draw1x2String(7, 0, " ");
                u8x8.drawString(10, 1, "   ");
                u8x8.draw1x2String(12, 3, " ");
                u8x8.drawString(10, 5, "   ");
                u8x8.draw1x2String(7, 6, " ");
                u8x8.drawString(2, 5, "    ");
                u8x8.draw1x2String(2, 3, " ");
                u8x8.drawString(2, 1, "    ");
            }
            // Best version so far : big circle in the middle
            if (lPos == 7)
            {
                u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
                u8x8.draw1x2String(7, 0, "\x8c");
                u8x8.drawString(10, 1, "Win");
                u8x8.draw1x2String(12, 3, "\x8d");
                u8x8.drawString(10, 5, "alt");
                u8x8.draw1x2String(7, 6, "\x8e");
                u8x8.drawString(2, 5, "ctrl");
                u8x8.draw1x2String(2, 3, "\x8b");
                u8x8.drawString(2, 1, "clic");
            }
            else if (controllerState == 4 && lPos < 5)
            {
                u8x8.setFont(u8x8_font_7x14_1x2_f);
                u8x8.drawUTF8(7, 0, toc->showChoice(controllerState, lPos, 3));
                u8x8.drawUTF8(10, 1, toc->showChoice(controllerState, lPos, 4));
                u8x8.drawUTF8(12, 3, toc->showChoice(controllerState, lPos, 5));
                u8x8.drawUTF8(10, 5, toc->showChoice(controllerState, lPos, 6));
                u8x8.drawUTF8(7, 6, toc->showChoice(controllerState, lPos, 7));
                u8x8.drawUTF8(4, 5, toc->showChoice(controllerState, lPos, 8));
                u8x8.drawUTF8(2, 3, toc->showChoice(controllerState, lPos, 1));
                u8x8.drawUTF8(4, 1, toc->showChoice(controllerState, lPos, 2));
            }
            else
            {
                u8x8.setFont(u8x8_font_7x14_1x2_f);

                for (int i = 1; i < 9; i++)
                {
                    Serial.println(toc->getChoice(controllerState, lPos, i));
                    Serial.println(char(toc->getChoice(controllerState, lPos, i)));
                }

                u8x8.drawGlyph(7, 0, toc->getChoice(controllerState, lPos, 3));
                u8x8.drawGlyph(10, 1, toc->getChoice(controllerState, lPos, 4));
                u8x8.drawGlyph(12, 3, toc->getChoice(controllerState, lPos, 5));
                u8x8.drawGlyph(10, 5, toc->getChoice(controllerState, lPos, 6));
                u8x8.drawGlyph(7, 6, toc->getChoice(controllerState, lPos, 7));
                u8x8.drawGlyph(4, 5, toc->getChoice(controllerState, lPos, 8));
                u8x8.drawGlyph(2, 3, toc->getChoice(controllerState, lPos, 1));
                u8x8.drawGlyph(4, 1, toc->getChoice(controllerState, lPos, 2));
            }
            oldLPos = lPos;
        }
    }
}

void Screen::draw_bar(uint8_t c, uint8_t is_inverse)
{
    uint8_t r;
    u8x8.setInverseFont(is_inverse);
    for (r = 0; r < u8x8.getRows(); r++)
    {
        u8x8.setCursor(c, r);
        u8x8.print(" ");
    }
}

void Screen::draw_ascii_row(uint8_t r, int start)
{
    int a;
    uint8_t c;
    for (c = 0; c < u8x8.getCols(); c++)
    {
        u8x8.setCursor(c, r);
        a = start + c;
        if (a <= 255)
            u8x8.write(a);
    }
}

void Screen::loop(TableOfCharacters *toc)
{
    updateMouse(0, 0);
    delay(1000);
    for (int j = 0; j < 2; j++)
    {
        for (int i = 1; i < 9; i++)
        {
            updateType(toc, j, i);
            delay(1000);
        }
    }
}
