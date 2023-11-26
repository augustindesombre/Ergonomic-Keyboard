#include "TableOfCharacters.h"

TableOfCharacters::TableOfCharacters()
{
    return;
}

const char *TableOfCharacters::showChoice(int controllerState, int lJoystickState, int rJoystickState)
{
    if (controllerState != 3)
    {
        return "?";
    }
    return list_accents[lJoystickState - 1][rJoystickState - 1];
}

uint16_t TableOfCharacters::getChoice(int controllerState, int lJoystickState, int rJoystickState)
{
    if (lJoystickState < 1 || lJoystickState > 8 || rJoystickState < 1 || rJoystickState > 8)
    {
        return "?";
    }
    if (lJoystickState < 5)
    {
        int result = 8 * (lJoystickState - 1) + (rJoystickState - 1);
        switch (controllerState)
        {
        case 0:
            result = result + 96;
            break;

        case 1:
            result = result + 64;
            break;

        case (2):
            result = result + 32;
            break;

        case (3):
            result = result + 128;
            break;
        }
        return result;
    }
    else
    {
        switch (lJoystickState)
        {
        case 5:
            return list5[rJoystickState - 1];
            break;
        case 6:
            return list6[rJoystickState - 1];
            break;
        case 8:
            return list8[rJoystickState - 1];
            break;
        }
    }
}
