// Logic to control the motion of the bot. Uses HBridge IC chip and two motors. 

int pinPotent1 = A0;
int pinPotent2 = A1;
int motorPos1 = 4;
int motorNeg1 = 5;
int motorPos2 = 2;
int motorNeg2 = 3;

bool turningClock1 = false;
bool turningCounter1 = false;
bool turningClock2 = false;
bool turningCounter2 = false;

int motorSpeed1;
int motorSpeed2;
void setup() {
    Serial.begin(9600);
    pinMode(motorPos1, OUTPUT);
    pinMode(motorNeg1, OUTPUT);
    pinMode(motorPos2, OUTPUT);
    pinMode(motorNeg2, OUTPUT);
}

void loop() {
    motorSpeed1 = map(analogRead(pinPotent1), 0, 1023, 50, 255);
    motorSpeed2 = map(analogRead(pinPotent2), 0, 1023, 50, 255);
    moveForward();
    delay(3000);
    completeStop();
    delay(1000);
    turnLeft90();
    delay(1000);
    turnRight90();
    delay(1000);
    moveBackward();
    delay(3000);
    completeStop();
    turnLeft180();
    delay(1000);
    turnRight180();
    delay(1000);
    turnLeft():
    delay(3000);
    turnRight();
    delay(3000);
}

void stopMotor1() {
     turningClock1 = false;
     turningCounter1 = false;
     digitalWrite(motorPos1, LOW);
     digitalWrite(motorNeg1, LOW);
}

void stopMotor2() {
     turningClock2 = false;
     turningCounter2 = false;
     digitalWrite(motorPos2, LOW);
     digitalWrite(motorNeg2, LOW);
}

void turnMotorClock1() {
    turningClock1 = true;
    turningCounter1 = false;
    analogWrite(motorPos1, motorSpeed1);
    digitalWrite(motorNeg1, LOW);
}

void turnMotorClock2() {
    turningClock2 = true;
    turningCounter2 = false;
    analogWrite(motorPos2, motorSpeed2);
    digitalWrite(motorNeg2, LOW);
}

void turnMotorCounter1() {
    turningClock1 = false;
    turningCounter1 = true;
    digitalWrite(motorPos1, LOW);
    analogWrite(motorNeg1, motorSpeed1);
}

void turnMotorCounter2() {
    turningClock2= false;
    turningCounter2 = true;
    digitalWrite(motorPos2, LOW);
    analogWrite(motorNeg2, motorSpeed2);
}

void moveForward() {
    //motorSpeed1 = 78;
    //motorSpeed2 = 70;
    turnMotorClock1();
    turnMotorCounter2();
}

void moveBackward() {
    //motorSpeed1 = 78;
    //motorSpeed2 = 70;
    turnMotorClock2();
    turnMotorCounter1();
}

void turnLeft() {
    motorSpeed2 = 180;
    stopMotor1();
    turnMotorCounter2();    
}

void turnRight() {
    motorSpeed1 = 180;
    stopMotor2();
    turnMotorClock1();    
}

void turnLeft90() {
    motorSpeed2 = 180;
    stopMotor1();
    turnMotorCounter2();
    delay(1000);
    stopMotor2();
}

void turnRight90() {
    motorSpeed1 = 180;
    stopMotor2();
    turnMotorClock1();
    delay(1000);
    stopMotor1();
}

void turnLeft180() {
    motorSpeed2 = 180;
    stopMotor1();
    turnMotorCounter2();
    delay(2000);
    stopMotor2();
}

void turnRight180() {
    motorSpeed1 = 180;
    stopMotor2();
    turnMotorClock1();
    delay(2000);
    stopMotor1();  
}

void completeStop() {
    stopMotor1();
    stopMotor2();
}
