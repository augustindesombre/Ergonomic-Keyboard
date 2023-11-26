#ifndef ERGOK_H
#define ERGOK_H

#include "Screen.h"
#include "Joystick.h"
#include "TableOfCharacters.h"
#include "Actioner.h"

class ErgoK
{
private:
    Joystick leftStick;
    Joystick rightStick;
    Screen screen;
    TableOfCharacters toc;
    Actioner action;
    int controllerState;
    int oldLState = 0;
    int oldRState = 0;
    bool writable = true;

public:
    ErgoK();
    void begin(int lXPin, int lYPin, int lClickPin, int rXPin, int rYPin, int rClickPin);
    void update();
    void toggleControllerState();
    void moveMouse();
    void updateClicks();
};

#endif