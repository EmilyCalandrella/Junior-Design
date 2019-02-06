// Controls one motor with discrete H-Bridge out of 2 PMOS and 2 NMOS (Good)
// Note: Switch1 and Switch3 are PMOS so logic LOW means the switch is ON.

int Switch1 = 2;
int Switch2 = 3;
int Switch3 = 4;
int Switch4 = 5;
int pinPotent = A0;

int motorSpeed;
long unsigned previousTime = 0;
boolean turningClock = true;
boolean turningCounter = false;


void setup() {
    Serial.begin(9600);
    pinMode(Switch1, OUTPUT);
    pinMode(Switch2, OUTPUT);
    pinMode(Switch3, OUTPUT);
    pinMode(Switch4, OUTPUT);
    turnMotorClock();
}

void loop() {
   motorSpeed = map(analogRead(pinPotent), 0, 1023, 0, 190);
   changeDirection();
   Serial.println(motorSpeed);
}

void changeDirection() {
  int waitTime = 2000;
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= waitTime) {
    previousTime = currentTime;
    if (turningClock) {
      stopMotor();
      turnMotorCounter();
    } else if (turningCounter) {
      stopMotor();
      turnMotorClock();
    }
  }
}


void stopMotor() {
     turningClock = false;
     turningCounter = false;
     digitalWrite(Switch1, LOW);
     digitalWrite(Switch2, LOW);
     digitalWrite(Switch3, LOW);
     digitalWrite(Switch4, LOW);
     delay(5);
}

void turnMotorClock() {
    turningClock = true;
    turningCounter = false;
    digitalWrite(Switch1, HIGH);
    digitalWrite(Switch2, HIGH);
    analogWrite(Switch3, motorSpeed);
    digitalWrite(Switch4, LOW);
}

void turnMotorCounter() {
  turningClock = false;
  turningCounter = true;
  analogWrite(Switch1, motorSpeed + 8);
  digitalWrite(Switch2, LOW);
  digitalWrite(Switch3, HIGH);
  digitalWrite(Switch4, HIGH);
}

