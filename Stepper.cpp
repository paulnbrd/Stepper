#include "Arduino.h"
#include "./Stepper.h"

Stepper::Stepper(int stepPin, int dirPin, unsigned long pulseTime)
{
    this->stepPin = stepPin;
    this->dirPin = dirPin;
    this->pulseTime = pulseTime;
    this->lastStepTime = 0;
    this->position = 0;

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
};
Stepper::Stepper(int stepPin, int dirPin) : Stepper(stepPin, dirPin, 500){};
void Stepper::step(bool direction)
{
    digitalWrite(dirPin, direction);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(this->pulseTime); // this delay is needed for most stepper drivers
    digitalWrite(stepPin, LOW);
    lastStepTime = micros();

    // Update position
    if (direction)
    {
        position++;
    }
    else
    {
        position--;
    }
};
void Stepper::runInDirection(bool direction, unsigned long interval)
{
    if (micros() - lastStepTime >= interval)
    {
        digitalWrite(dirPin, direction);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(this->pulseTime); // this delay is needed for most stepper drivers
        digitalWrite(stepPin, LOW);
        lastStepTime = micros();

        // Update position
        if (direction)
        {
            position++;
        }
        else
        {
            position--;
        }
    }
};

long Stepper::getPosition()
{
    return position;
};
void Stepper::resetPosition(long position)
{
    this->position = position;
}
void Stepper::resetPosition()
{
    resetPosition(0);
}

/**
 * @brief Move the stepper to a position in a given time
 * @param position The position to move to
 * @param time The time to take to move to the position in microseconds
 */
void Stepper::goToIn(long position, unsigned long time)
{
    long steps = position - this->position;
    unsigned long stepTime = time / abs(steps);
    if (steps > 0)
    {
        while (this->position < position)
        {
            step(true);
            delayMicroseconds(stepTime);
        }
    }
    else
    {
        while (this->position > position)
        {
            step(false);
            delayMicroseconds(stepTime);
        }
    }
}
