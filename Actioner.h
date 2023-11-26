#ifndef ACTIONER_H
#define ACTIONER_H

#include <Keyboard.h>
#include <Mouse.h>

class Actioner
{
private:
    bool active;
    bool ctrlPressed;
    bool altPressed;
    bool mousePressed;

public:
    // Constructor
    Actioner();
    void begin();

    // Methods
    void onOff();
    void moveMouse(float x, float y);
    void type(int letter);

    void leftClick();
    void rightClick();

    bool isSpecialKey(int lPos, int rPos, int controllerState);

    void keypad(int letter);
};

#endif