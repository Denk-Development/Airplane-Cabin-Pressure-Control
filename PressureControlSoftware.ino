#include "TargetPressureDelta.h"
#include "DisplayController.h"

void setup() {
  Serial.begin(9600);
  DisplayController::init();
}

void loop() {
  float targetPsi = getTargetPressureDelta();
  DisplayController::showPressureSelection(targetPsi);
}
