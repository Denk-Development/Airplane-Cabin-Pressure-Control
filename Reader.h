#ifndef READER_H
#define READER_H

#include "Arduino.h"


const uint8_t targetPressurePin = A2,
    measuredPressurePin = A1;


float getTargetPressureDelta() {
    // returns the target pressure delta in PSI
    // guaranteed to be in [0, 4.5]

    int rawVal = analogRead(targetPressurePin);
    float psi = map(rawVal, 0, 634, 0, 4500) / 1000.;

    // chop to [0, 4.5]
    psi = max(0, psi);
    psi = min(4.5, psi);

    return psi;
}


float getPressureMeasuredDelta() {
    // returns the measured pressure delta in PSI
    // no guarantee on bounds of this value

    int rawVal = analogRead(measuredPressurePin);
    float psi = map(rawVal, 0, 634, 0, 4500) / 1000.;

    return psi;
}

#endif
