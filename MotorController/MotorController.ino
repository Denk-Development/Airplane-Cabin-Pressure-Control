const int pwm = 3;  // PWM control for motor outputs 1 and 2 
const int dir = 2;  // direction control for motor outputs 1 and 2 
const int forwardControlPin = 7,
  backwardControlPin = 6;

void setup()
{
  pinMode(forwardControlPin, INPUT_PULLUP);
  pinMode(backwardControlPin, INPUT_PULLUP);
  
  // set control pins to be outputs
  pinMode(pwm, OUTPUT);
  pinMode(dir, OUTPUT);

  // set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm, 100);
}

void loop()
{
  bool fwd = digitalRead(forwardControlPin) == HIGH;
  bool bwd = digitalRead(backwardControlPin) == HIGH;
  
  if (fwd && !bwd) {
    // forward
    digitalWrite(dir, LOW); 
    analogWrite(pwm, 255);  
  }
  else if (bwd && !fwd) {
    // backward
    digitalWrite(dir, HIGH); 
    analogWrite(pwm, 255);  
  }
  else {
    // neutral
    analogWrite(pwm, 0);  
  }

  delay(100);
}
