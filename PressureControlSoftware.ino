#include "Reader.h"
#include "Display.h"
#include "Valve.h"

// #define SERIAL_DEBUG 0

const float minOpening = 0.05, 
  maxOpeningAtPsiDelta = 1.5,
  toleratedPsiDelta = 0.1;

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

  if (absDelta > toleratedPsiDelta) {
    float proportional = computeProportional(delta);
    return min(proportional, 1.);
  }
  
  return 0.;
}

float computeProportional(float delta) {
  delta = max(delta, 0.); // make sure delta is positive
  
  float m = (1. - minOpening) / maxOpeningAtPsiDelta;
  float b = minOpening;
  
  float proportional = m * delta + b;

  return proportional;
}
