#include "ErgoK.h"

ErgoK::ErgoK()
{
    controllerState = 0;
    TableOfCharacters toc();
}

void ErgoK::begin(int lXPin, int lYPin, int lClickPin, int rXPin, int rYPin, int rClickPin)
{
    leftStick.begin(lXPin, lYPin, lClickPin);
    rightStick.begin(rXPin, rYPin, rClickPin);
    leftStick.setOffset(2);
    rightStick.setOffset(6);
    screen.begin();
    action.begin();
}

void ErgoK::update()
{
    int lClick = leftStick.getClickState();
    int rClick = rightStick.getClickState();
    int lPos = leftStick.getPositionState();
    int rPos = rightStick.getPositionState();

    switch (lClick)
    {
    case 1:
        toggleControllerState();
        // Serial.println("L 1 Pressed");
        break;

    case 2:
        screen.onOff();
        action.onOff();
        // Serial.println("L 2 Pressed");
        break;

    default:
        switch (rClick)
        {
        case 1:
            action.leftClick();
            Serial.println("R 1 Pressed");
            break;

        case 2:
            action.rightClick();
            Serial.println("R 2 Pressed");
            break;

        default:
            if (lPos == 0)
            {

                screen.updateMouse(rightStick.getXPosition(), rightStick.getYPosition());
                action.moveMouse(rightStick.getXPosition(), rightStick.getYPosition());
            }
            else
            {
                screen.updateType(&toc, controllerState, lPos);
                if (rPos != 0 && writable)
                {
                    if (!action.isSpecialKey(lPos, rPos, controllerState))
                    {
                        int encodedLetter = toc.getChoice(controllerState, lPos, rPos);
                        action.type(encodedLetter);
                    }
                    writable = false;
                }
                if (rPos == 0)
                {
                    writable = true;
                }
            }
        }
    }
}

void ErgoK::toggleControllerState()
{
    controllerState = (controllerState + 1) % 4;
}

void ErgoK::updateClicks()
{
    leftStick.updateClick();
    rightStick.updateClick();
}
