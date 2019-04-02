const int pwm = 3;  // PWM control for motor outputs 1 and 2 
const int dir = 2;  // direction control for motor outputs 1 and 2 
const int motorSlowPin = 5,
  forwardControlPin = 7,
  backwardControlPin = 6;

const int slowSpeed = 200, // in [0,1000]
  fastSpeed = 1000; // in [0, 1000]

uint8_t motorSpeed = 200; // in [0,255]

void setup()
{
  pinMode(forwardControlPin, INPUT_PULLUP);
  pinMode(backwardControlPin, INPUT_PULLUP);
  pinMode(motorSlowPin, INPUT_PULLUP);
  
  // set control pins to be outputs
  pinMode(pwm, OUTPUT);
  pinMode(dir, OUTPUT);
}

void loop()
{
  unsigned long lastMillis = 0;
  while (true) {
    unsigned long currentMillis = millis();
    if (currentMillis < lastMillis) {
      lastMillis = currentMillis;
      continue;
    }
    lastMillis = currentMillis;

    bool fwd = digitalRead(forwardControlPin) == HIGH;
    bool bwd = digitalRead(backwardControlPin) == HIGH;
    bool slow = digitalRead(motorSlowPin) == HIGH;
    
    if (fwd && !bwd) {
      // forward
      digitalWrite(dir, LOW); 
      analogWrite(pwm, motorSpeed);  
    }
    else if (bwd && !fwd) {
      // backward
      digitalWrite(dir, HIGH); 
      analogWrite(pwm, motorSpeed);  
    }
    else {
      // neutral
      analogWrite(pwm, 0);  
    }

    // turn motor only for a certain period of time
    int onDelay = slow ? slowSpeed : fastSpeed;
    delay(onDelay);
    if (onDelay < 1000) {
      analogWrite(pwm, 0);
      delay(1000-onDelay);
    }
  }
}
