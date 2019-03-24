#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>

// motor sample code
// https://www.velleman.eu/support/downloads/?code=VMA03

const uint8_t openingPin = A0,
    motorBackwardPin = 6,
    motorForwardPin = 7; 

const float openingTolerance = 0.1;
const float targetTolerance = openingTolerance / 2;

class Valve
{
public:
    static void init() {
        pinMode(motorBackwardPin, OUTPUT);
        pinMode(motorForwardPin, OUTPUT);
        digitalWrite(motorBackwardPin, HIGH);
        digitalWrite(motorForwardPin, HIGH);
        moving = false;
    };

    static float getOpening() {
        // returns the valve state in [0,1], where 0 is closed and 1 is open

        int rawVal = analogRead(openingPin);
        float opening = map(rawVal, 0, 767, 0, 1000) / 1000.;

        return opening;
    };

    static void setOpening(float target) {
        target = min(target, 1.);
        target = max(target, 0.);
        float actual = Valve::getOpening();

        float delta = target - actual;
        float absDelta = abs(delta);

        if (moving) {
            if (absDelta < targetTolerance) {
                stop();
            }
            else {
                move(delta > 0);
            }
        }
        else {
            if (absDelta > openingTolerance) {
                move(delta > 0);
            }
        }
    };

private:
    static bool moving;

    static void stop() {
        moving = false;
        digitalWrite(motorBackwardPin, HIGH);
        digitalWrite(motorForwardPin, HIGH);

    };

    static void move(bool forward) {
        moving = true;
        digitalWrite(motorBackwardPin, !forward);
        digitalWrite(motorForwardPin, forward);
    };
};

bool Valve::moving = false;

#endif
