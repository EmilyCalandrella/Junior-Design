// Controlling one motor using 4 NMOS discrete H-Bridge (Bad)
// Can set the motor speed with potentiometer, direction changes every few seconds.

int pinPotent = A0;
int pinSpeed = 7;
int pinBackward = 3;
int pinForward = 4;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinSpeed, OUTPUT);
  pinMode(pinBackward, OUTPUT);
  pinMode(pinForward, OUTPUT);

  digitalWrite(pinBackward, LOW);
  digitalWrite(pinForward, LOW);
}

void loop() {
  int motorSpeed;
  motorSpeed = map(analogRead(pinPotent), 0, 1023, 0, 255); 
  analogWrite(pinSpeed, motorSpeed);
  flipPolarity();
}

void flipPolarity() {
    int waitTime = 3000;
    unsigned long currentTime = millis();
    if (currentTime - previousTime >= waitTime) {
      previousTime = currentTime;
      if (digitalRead(pinBackward) == HIGH) {
        digitalWrite(pinBackward, LOW);
        delay(10);
        digitalWrite(pinForward, HIGH);
      } else {
        digitalWrite(pinForward, LOW);
        delay(10);
        digitalWrite(pinBackward, HIGH);        
      }
    }
}

