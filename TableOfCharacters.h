#ifndef TABLE_OF_CHARACTERS_H
#define TABLE_OF_CHARACTERS_H

#include <Arduino.h>

class TableOfCharacters
{
private:
    uint16_t list5[8] =
        {'<', '0', '1', '\xab', ' ', '\xbb', '\xb6', ' '};

    uint16_t list6[8] =
        {'7', '8', '9', '2', '3', '4', '5', '6'};

    uint16_t list8[8] =
        {'/', '\'', '.', ',', ';', ':', '!', '?'};

    const char *list_accents[4][8] = {
        {"Ç", "ü", "é", "â", "ä", "à", "å", "ç"},
        {"ê", "ë", "è", "ï", "î", "ì", "Ä", "Å"},
        {"É", "æ", "Æ", "ô", "ö", "ò", "û", "ù"},
        {"ÿ", "Ö", "Ü", "¢", "£", "¥", "₧", "ƒ"}};

public:
    TableOfCharacters();
    const char *showChoice(int controllerState, int leftPosition, int rightPosition);
    uint16_t getChoice(int controllerState, int leftPosition, int rightPosition);
};

#endif