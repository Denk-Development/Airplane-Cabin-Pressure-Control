#ifndef VALVE_H
#define VALVE_H

#include "Parameters.h"
#include <Arduino.h>

#define VALVE_MOTOR_REVERSED false

// motor sample code
// https://www.velleman.eu/support/downloads/?code=VMA03

const uint8_t openingPin = A0,
    motorSlowPin = 5,
    motorBackwardPin = 6,
    motorForwardPin = 7;

class Valve
{
public:
    static void init() {
        pinMode(motorBackwardPin, OUTPUT);
        pinMode(motorForwardPin, OUTPUT);
        pinMode(motorSlowPin, OUTPUT);
        digitalWrite(motorBackwardPin, HIGH);
        digitalWrite(motorForwardPin, HIGH);
        digitalWrite(motorSlowPin, LOW);
        moving = false;
    };

    static float getOpening() {
        // returns the valve state in [0,1], where 0 is closed and 1 is open

        int rawVal = analogRead(openingPin);
        float opening = map(rawVal, 0, 767, 0, 1000) / 1000.;

        return opening;
    };

    static void setOpening(float target) {
        // sets the valve opening target
        // depending on the current state, the motor will be engaged

        target = min(target, 1.);
        target = max(target, 0.);
        float actual = getOpening();

        float delta = target - actual;
        float absDelta = abs(delta);

        if (actual == target) {
            stop();
            return;
        }

        // for complete opening / closing keep moving
        // a mechanical solution prevents the motor from taking damage
        if (target == 0.) {
            move(false);
            return;
        }
        if (target == 1.) {
            move(true);
            return;
        }

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

    static void open() {
        move(true);
    };

    static void close() {
        move(false);
    };

    static void move(bool forward) {
        forward ^= VALVE_MOTOR_REVERSED;
        moving = true;
        digitalWrite(motorBackwardPin, !forward);
        digitalWrite(motorForwardPin, forward);
    };

    static void stop() {
        moving = false;
        digitalWrite(motorBackwardPin, HIGH);
        digitalWrite(motorForwardPin, HIGH);
    };

    static void setSlow(bool slow) {
        digitalWrite(motorSlowPin, slow);
    };

private:
    static bool moving;
};

bool Valve::moving = false;

#endif
