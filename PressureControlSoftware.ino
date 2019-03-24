#include "Reader.h"
#include "Display.h"
#include "Valve.h"

// #define SERIAL_DEBUG 0

void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(9600);
    Serial.println("Starting...");
  #endif
  Display::init();
  Valve::init();
}

void loop() {
  float targetPsi = getTargetPressureDelta();
  float measuredPsi = getPressureMeasuredDelta();
  float offPsi = targetPsi - measuredPsi;

  float valveOpening = Valve::getOpening();

  #ifndef SERIAL_DEBUG
    Display::showPressureSelection(targetPsi);
    Display::showValveOpening(valveOpening);
    Display::submit();
  #endif

  float valveOpeningTarget = computeValveOpeningTarget(targetPsi, measuredPsi);
  Valve::setOpening(valveOpeningTarget);

  #ifdef SERIAL_DEBUG
    Serial.print("Off by: ");
    Serial.print(offPsi, 2);
    Serial.println(" psi");
  #endif
}

float computeValveOpeningTarget(float targetPsi, float measuredPsi) {
  float delta = measuredPsi - targetPsi;
  float absDelta = abs(delta);

  if (delta < 0) {
    return 0.;
  }

  if (absDelta > 0.1) {
    return 0.4;
  }
  else {
    return 0.;
  }
}
