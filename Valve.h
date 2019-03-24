#ifndef VALVE_H
#define VALVE_H

#include <Arduino.h>

// motor sample code
// https://www.velleman.eu/support/downloads/?code=VMA03

const uint8_t openingPin = A0;

class Valve
{
public:
    static void init() {
    };

    static float getOpening() {
        // returns the valve state in [0,1], where 0 is closed and 1 is open

        int rawVal = analogRead(openingPin);
        float opening = map(rawVal, 0, 767, 0, 1000) / 1000.;

        return opening;
    };

    static void setOpening(float opening) {

    }
};

#endif
