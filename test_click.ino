#include <Arduino.h>
#include "Click.h"

Click lclick(A2);
Click rclick(A5);

void updateClicks()
{
    lclick.update();
    rclick.update();
}

void setupClick()
{
    pinMode(A2, INPUT);
    pinMode(A5, INPUT);
    pinMode(7, INPUT);
    attachInterrupt(digitalPinToInterrupt(7), updateClicks, CHANGE);
}

void loopClick()
{
    //test_screen(lclick.getState() * 100 + rclick.getState());
}
