#include "Parameters.h"
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
  float prevValveTarget = Valve::getOpening();
  float valveOpeningTarget = prevValveTarget;
  long valveLastUpdatedMillis = millis();
  
  while (true) {
    long currentMillis = millis();
    float targetPsi = getTargetPressureDelta();
    float measuredPsi = getPressureMeasuredDelta();
    float offPsi = targetPsi - measuredPsi;
  
    float valveOpening = Valve::getOpening();

    if (currentMillis < valveLastUpdatedMillis) {
      // handle millis overflow case
      continue;
    }
    if (currentMillis - valveLastUpdatedMillis >= 100) {
      valveLastUpdatedMillis = currentMillis;
      
      //float valveOpeningTarget = computeValveOpeningTarget(targetPsi, measuredPsi);

      if (abs(offPsi) > toleratedPsiDelta) {
        // only update if the tolerated threshold is exceeded
        valveOpeningTarget = prevValveTarget - offPsi * valveSpeed;
        valveOpeningTarget = min(1., max(0., valveOpeningTarget));
        Valve::setOpening(valveOpeningTarget);
        prevValveTarget = valveOpeningTarget;
      }
    }
    
    #ifndef SERIAL_DEBUG
      Display::showPressureSelection(measuredPsi, targetPsi);
      Display::showValveOpening(valveOpening, valveOpeningTarget);
      Display::submit();
    #endif
  
    #ifdef SERIAL_DEBUG
      Serial.print("Off by: ");
      Serial.print(offPsi, 2);
      Serial.println(" psi");
    #endif
  }
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
  
  float proportional = m * delta + b;

  return proportional;
}
