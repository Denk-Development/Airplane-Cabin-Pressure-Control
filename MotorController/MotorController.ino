const int pwm_a = 3;  // PWM control for motor outputs 1 and 2 
const int pwm_b = 9;  // PWM control for motor outputs 3 and 4 
const int dir_a = 2;  // direction control for motor outputs 1 and 2 
const int dir_b = 8;  // direction control for motor outputs 3 and 4 
const int forwardControlPin = 7,
  backwardControlPin = 6;

void setup()
{
  pinMode(forwardControlPin, INPUT_PULLUP);
  pinMode(backwardControlPin, INPUT_PULLUP);
  
  // set control pins to be outputs
  pinMode(pwm_a, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  // set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_a, 100);
  analogWrite(pwm_b, 100); 
}

void loop()
{
  bool fwd = digitalRead(forwardControlPin) == HIGH;
  bool bwd = digitalRead(backwardControlPin) == HIGH;
  
  if (fwd && !bwd) {
    // forward
    digitalWrite(dir_a, LOW); 
    digitalWrite(dir_b, LOW);  
    
    analogWrite(pwm_a, 255);  
    analogWrite(pwm_b, 255);
  }
  else if (bwd && !fwd) {
    // backward
    digitalWrite(dir_a, HIGH); 
    digitalWrite(dir_b, HIGH);  
    
    analogWrite(pwm_a, 255);  
    analogWrite(pwm_b, 255);
  }
  else {
    // neutral
    analogWrite(pwm_a, 0);  
    analogWrite(pwm_b, 0);
  }
}
