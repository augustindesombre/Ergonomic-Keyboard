// Display > https://pmdway.com/products/0-96-128-64-graphic-oled-displays-i2c-or-spi-various-colors

#include <Arduino.h>
#include "Screen.h"
#include "TableOfCharacters.h"

Screen screen;
TableOfCharacters *toc = new TableOfCharacters();

void setup1(void)
{
  screen.begin();
  screen.mouseMode();
}

void loop1(void)
{
  screen.loop(toc);
}
