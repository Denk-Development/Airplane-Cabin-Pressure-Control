#ifndef TARGET_PRESSURE_DELTA_H
#define TARGET_PRESSURE_DELTA_H

#include "Arduino.h"

const uint8_t targetPressurePin = A2;

float getTargetPressureDelta() {
	// returns the target pressure delta in PSI

	int rawVal = analogRead(targetPressurePin);
	float psi = map(rawVal, 0, 634, 0, 4500) / 1000.;

	// chop to [0, 4.5]
	psi = max(0, psi);
	psi = min(4.5, psi);

	return psi;
}

#endif