#ifndef STEPPER_H
#define STEPPER_H

#include "Arduino.h"

class Stepper
{
private:
    int stepPin;
    int dirPin;
    long position;
    unsigned long pulseTime;
    unsigned long lastStepTime;

public:
    Stepper(int stepPin, int dirPin, unsigned long pulseTime);
    Stepper(int stepPin, int dirPin);
    void step(bool direction);
    void runInDirection(bool direction, unsigned long interval);

    long getPosition();
    void resetPosition();
    void resetPosition(long position);

    void goToIn(long position, unsigned long time);
};

#endif // STEPPER_H