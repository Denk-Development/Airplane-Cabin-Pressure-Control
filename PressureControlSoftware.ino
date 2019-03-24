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

  Valve::setOpening(offPsi);

  #ifdef SERIAL_DEBUG
    Serial.print("Off by: ");
    Serial.print(offPsi, 2);
    Serial.println(" psi");
  #endif
}
