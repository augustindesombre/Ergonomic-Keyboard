#include "Joystick.h"

Joystick leftj;
Joystick rightj;

void updateJoystickClicks()
{
    leftj.updateClick();
    rightj.updateClick();
}

void setupJoystick()
{
  leftj.begin(A0, A1, A2);
  rightj.begin(A3, A4, A5);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A2, INPUT);
    pinMode(A5, INPUT);
    pinMode(7, INPUT);
    attachInterrupt(digitalPinToInterrupt(7), updateJoystickClicks, CHANGE);
    Serial.begin(9600);
    delay(1000);
//    test_screen(1234);
    delay(1000);
}

void loopJoystick()
{
    Serial.println(leftj.getPositionState());
//    test_screen(10000+leftj.getPositionState()*1000+leftj.getClickState() * 100 + rightj.getPositionState()*10+rightj.getClickState());
    delay(100);
}
