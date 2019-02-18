// Program to flash red and blue LEDs and find path using photodiode

// Constants for Sensors
int bluePin = 6;
int redPin = 7;
int photoPin = A1;
int path = 0;
  // 1 = yellow
  // 2 = blue
  // 3 = red
  // 4 = black
int voltage = 0;
int threshold = 80;

// Constants for motion
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  /*digitalWrite(bluePin,HIGH);
  delay(1000);
  voltage = analogRead(photoPin);
  Serial.print("blue: ");
  Serial.println(voltage);
  digitalWrite(bluePin,LOW);
  digitalWrite(redPin,HIGH);
  delay(1000);
  voltage = analogRead(photoPin);
  Serial.print("red: ");
  Serial.println(voltage);
  digitalWrite(redPin,LOW);
  */
  // Determine path color
  determineColor();
  delay(500);
  

}


/*****************
 SENSOR FUNCTIONS
 *****************/

int determineColor() {
  // Start with both LEDs off
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  
  // Turn blue LED on
  digitalWrite(bluePin, HIGH);
  delay(1000);
  
  // Read voltage from photosensor
  voltage = analogRead(photoPin);
  Serial.print("blue: ");
  Serial.println(voltage);

  // If voltage from blue flash is high, the path is yellow or red
  if (voltage > threshold) {
      // Turn blue LED off and red LED on
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
      delay(1000);
      
      // Read voltage from photosensor
      voltage = analogRead(photoPin);
      Serial.print("red: ");
      Serial.println(voltage);
      
      if (voltage > threshold) {
        path = 1; // yellow
        Serial.println("Path is yellow");
      }
      else {
        path = 2; // blue
        Serial.println("Path is blue");
      }
    }

    // If voltage from blue flash is low, path is blue or black
    else {
      // turn off blue LED, turn on red
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
      delay(1000);
      
      // check voltage from photosensor
      voltage = analogRead(photoPin);
      Serial.print("red: ");
      Serial.println(voltage);
      
      if (voltage > threshold) {
        path = 3; // red
        Serial.println("Path is red");
      }
      else {
        path = 4; // black
        Serial.println("Path is black");
      }
    } 
    return path; 
}

// Function to move along blue path in straigth line
// In order to work, this function will need to be in the main loop by itself.
// Otherwise it will go forward until it drifts off the path once, correct itself,
// and then stop.
void followBlue() {
  int color = determineColor();
  while (color == 2) {
    moveforward();
    delay(5000);
    color = determineColor();
  }
  while (color != 2) {
    turnLeft();
    delay(300);
    color = determineColor();
  }
  
}*/

// Function to move forward and stop when blue tape is detected
void stopAtBlue() {
  int color = determineColor();
  while (color != 2) {
    moveForward();
    delay(1000);
    color = determineColor();
  }
  completeStop();
}


/*******************
  MOTION FUNCTIONS
 ******************/

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
    motorSpeed1 = 83;
    motorSpeed2 = 70;
    turnMotorClock1();
    turnMotorCounter2();
}

void moveBackward() {
    motorSpeed1 = 80;
    motorSpeed2 = 70;
    turnMotorClock2();
    turnMotorCounter1();
}

void turnLeft() {
    motorSpeed2 = 100;
    stopMotor1();
    turnMotorCounter2();    
}

void turnRight() {
    motorSpeed1 = 100;
    stopMotor2();
    turnMotorClock1();    
}

void turnLeft90() {
    motorSpeed2 = 180;
    stopMotor1();
    turnMotorCounter2();
    delay(850);
    stopMotor2();
}

void turnRight90() {
    motorSpeed1 = 180;
    stopMotor2();
    turnMotorClock1();
    delay(900);
    stopMotor1();
}

void turnLeft180() {
    motorSpeed2 = 180;
    stopMotor1();
    turnMotorCounter2();
    delay(1700);
    stopMotor2();
}

void turnRight180() {
    motorSpeed1 = 180;
    stopMotor2();
    turnMotorClock1();
    delay(1800);
    stopMotor1();  
}

void completeStop() {
    stopMotor1();
    stopMotor2();
}

