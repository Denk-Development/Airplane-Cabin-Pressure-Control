#include "Reader.h"
#include "DisplayController.h"

//#define SERIAL_DEBUG 0

void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(9600);
    Serial.println("Starting...");
  #endif
  DisplayController::init();
}

void loop() {
  float targetPsi = getTargetPressureDelta();
  float measuredPsi = getPressureMeasuredDelta();
  float offPsi = targetPsi - measuredPsi;

  float valveOpening = getValveOpening();

  #ifndef SERIAL_DEBUG
    DisplayController::showPressureSelection(targetPsi);
    DisplayController::showValveOpening(valveOpening);
    DisplayController::submit();
  #endif

  #ifdef SERIAL_DEBUG
    Serial.print("Off by: ");
    Serial.print(offPsi, 2);
    Serial.println(" psi");
  #endif
}
