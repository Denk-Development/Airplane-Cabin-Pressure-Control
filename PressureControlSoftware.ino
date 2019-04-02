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
  unsigned long valveLastUpdatedMillis = millis();
  
  while (true) {
    unsigned long currentMillis = millis();
    if (currentMillis < valveLastUpdatedMillis) {
      // handle millis overflow case
      continue;
    }
    
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
    // stop the motor depending on the motor speed
    if (currentMillis % 1000 > motorSpeed) {
      Valve::stop();
      continue;
    }
    if (abs(offPsi) > toleratedPsiDelta) {
      Valve::move(offPsi < 0);  // open or close depending on inequality
    }
    else {
      Valve::stop();
    }
  }
}
