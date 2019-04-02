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
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, !digitalRead(13));  // activity indicator
  
  float targetPsi = getTargetPressureDelta();
  float measuredPsi = getPressureMeasuredDelta();
  float offPsi = targetPsi - measuredPsi;

  float valveOpening = Valve::getOpening();

  #ifndef SERIAL_DEBUG
    Display::showPressureSelection(measuredPsi, targetPsi);
    Display::showValveOpening(valveOpening, 0.f);
    Display::submit();
  #endif

  #ifdef SERIAL_DEBUG
    Serial.print("Off by: ");
    Serial.print(offPsi, 2);
    Serial.println(" psi");
  #endif

  // motor movement
  if (abs(offPsi) > toleratedPsiDelta) {
    Valve::move(offPsi < 0);  // open or close depending on inequality
  }
  else {
    Valve::stop();
  }
  Valve::setSlow(abs(offPsi) < lowSpeedPsiDelta); // control speed
}
