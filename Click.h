#ifndef CLICK_H
#define CLICK_H

#define TIME_INBETWEEN_CLICKS 300 // in millis
#define TIME_DOUBLE_CLICK 300     // in millis

class Click
{
private:
    int clickPin;
    int state;
    bool pressed;
    unsigned long lastChange; // in millis
    unsigned long lastClick;

public:
    // Constructor
    Click();
    Click(int _clickPin);

    // Getters
    int getState();

    void update();

    bool isPressed();
};

#endif
