#include "Actioner.h"

#include <Keyboard.h>
#include <Mouse.h>

Actioner::Actioner()
{
    active = true;
    ctrlPressed = false;
    altPressed = false;
    mousePressed = false;
}

void Actioner::begin()
{
    Keyboard.begin(KeyboardLayout_fr_FR);
    Mouse.begin();
}

void Actioner::onOff()
{
    active = !active;
}

void Actioner::moveMouse(float x, float y)
{
    float consigneX;
    float consigneY;
    if (active)
    {
        consigneX = pow(x * 0.75, 1) / (1.2 - pow(x, 2));
        consigneY = pow(y * 0.75, 1) / (1.2 - pow(y, 2));
        if (true)
        {
            Mouse.move(consigneX, consigneY);
        }
    }
}

void Actioner::type(int letter)
{
    if (active)
    {
        Keyboard.press(KEY_LEFT_ALT);
        keypad(letter);
        Keyboard.release(KEY_LEFT_ALT);
    }
}

void Actioner::leftClick()
{
    if (active)
    {
        Mouse.click(MOUSE_LEFT);
        ctrlPressed = false;
        altPressed = false;
        mousePressed = false;
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release(KEY_RIGHT_ALT);
        Mouse.release(MOUSE_LEFT);
    }
}

void Actioner::rightClick()
{
    if (active)
    {
        Mouse.click(MOUSE_RIGHT);
    }
}

bool Actioner::isSpecialKey(int lPos, int rPos, int controllerState)
{
    if (lPos == 5 && rPos == 1)
    {
        Keyboard.write(KEY_BACKSPACE);
        return true;
    }
    else if (lPos == 5 && rPos == 7)
    {
        Keyboard.write(KEY_RETURN);
        return true;
    }
    else if (lPos == 5 && rPos == 4)
    {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write(KEY_TAB);
        Keyboard.release(KEY_LEFT_SHIFT);
        return true;
    }
    else if (lPos == 5 && rPos == 6)
    {
        Keyboard.write(KEY_TAB);
        return true;
    }
    else if (lPos == 5 && rPos == 5)
    {
        Keyboard.write(uint8_t(' '));
        return true;
    }
    else if (lPos == 7)
    {
        if (rPos == 1)
        {
            Keyboard.write(KEY_LEFT_ARROW);
        }
        else if (rPos == 2)
        {
            if (mousePressed)
            {
                Mouse.release(MOUSE_LEFT);
            }
            else
            {
                Mouse.press(MOUSE_LEFT);
            }
            mousePressed = !mousePressed;
        }
        else if (rPos == 3)
        {
            Keyboard.write(KEY_UP_ARROW);
        }
        else if (rPos == 4)
        {
            Keyboard.write(KEY_LEFT_GUI);
        }
        else if (rPos == 5)
        {
            Keyboard.write(KEY_RIGHT_ARROW);
        }
        else if (rPos == 6)
        {
            if (altPressed)
            {
                Keyboard.release(KEY_RIGHT_ALT);
            }
            else
            {
                Keyboard.press(KEY_RIGHT_ALT);
            }
            altPressed = !altPressed;
        }
        else if (rPos == 7)
        {
            Keyboard.write(KEY_DOWN_ARROW);
        }
        else if (rPos == 8)
        {
            if (ctrlPressed)
            {
                Keyboard.release(KEY_LEFT_CTRL);
            }
            else
            {
                Keyboard.press(KEY_LEFT_CTRL);
            }
            ctrlPressed = !ctrlPressed;
        }
        return true;
    }
    return false;
}

void Actioner::keypad(int letter)
{
    int type;
    for (int i = 2; i > -1; i--)
    {
        int diviseur = 1;
        for (int j = 0; j < i; j++)
        {
            diviseur *= 10;
        }
        type = letter / diviseur;
        letter = letter % diviseur;

        if (type == 0)
        {
            Keyboard.write(KEY_KP_0);
        }
        else if (type == 1)
        {
            Keyboard.write(KEY_KP_1);
        }
        else if (type == 2)
        {
            Keyboard.write(KEY_KP_2);
        }
        else if (type == 3)
        {
            Keyboard.write(KEY_KP_3);
        }
        else if (type == 4)
        {
            Keyboard.write(KEY_KP_4);
        }
        else if (type == 5)
        {
            Keyboard.write(KEY_KP_5);
        }
        else if (type == 6)
        {
            Keyboard.write(KEY_KP_6);
        }
        else if (type == 7)
        {
            Keyboard.write(KEY_KP_7);
        }
        else if (type == 8)
        {
            Keyboard.write(KEY_KP_8);
        }
        else if (type == 9)
        {
            Keyboard.write(KEY_KP_9);
        }
    }
}
