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
int threshold = 95;
int flashTime = 125;
bool onBlue = false;
int color = 0;
bool lastCheck= 1; // 0 = left, 1 = right

// Constants for motion
//int pinPotent1 = A0;
int motorPos1 = 4;
int motorNeg1 = 5;
int motorPos2 = 2;
int motorNeg2 = 3;

bool turningClock1 = false;
bool turningCounter1 = false;
bool turningClock2 = false;
bool turningCounter2 = false;

int motorSpeed1 = 50;
int motorSpeed2 = 50;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorPos1, OUTPUT);
  pinMode(motorNeg1, OUTPUT);
  pinMode(motorPos2, OUTPUT);
  pinMode(motorNeg2, OUTPUT);
  
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  completeStop();
}

void loop() {
  // Determine path color
  //stopAtBlue();
  color = determineColor();
  blueArc90();
  //followBlue();
}


/*****************
 SENSOR FUNCTIONS
 *****************/

// Function to determine what color path the robot is on
int determineColor() {
  // Start with both LEDs off
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  
  // Turn blue LED on
  digitalWrite(bluePin, HIGH);
  delay(flashTime);
  
  // Read voltage from photosensor
  voltage = analogRead(photoPin);
  Serial.print("blue: ");
  Serial.println(voltage);
  delay(20);

  // If voltage from blue flash is high, the path is yellow or red
  if (voltage > threshold) {
      // Turn blue LED off and red LED on
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
      delay(flashTime);
      
      // Read voltage from photosensor
      voltage = analogRead(photoPin);
      Serial.print("red: ");
      Serial.println(voltage);
      delay(20);
      
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
      delay(flashTime);
      
      // check voltage from photosensor
      voltage = analogRead(photoPin);
      Serial.print("red: ");
      Serial.println(voltage);
      delay(20);
      
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



void checkLeft(int speed, int time) {
  completeStop();
  delay(10);
  turnLeft(speed);
  delay(time);
  completeStop();
  color = determineColor();  
}

void checkRight(int speed, int time) {
  completeStop();
  delay(10);
  turnRight(speed);
  delay(time);
  completeStop();
  color = determineColor();
}

/**** Should we take delays out of this function? (Between moving and determining color) ******/

// Function to move along blue path in straight line
// In order to work, this function will need to be in the main loop by itself.
// Otherwise it will go forward until it drifts off the path once, correct itself,
// and then stop.
void followBlue() {
  while (color == 2) {
    moveForward(55);
    color = determineColor();
  }

  completeStop();
  delay(10);
  moveBackward(60);
  delay(200);
  checkLeft(60, 250);
  
  if (color != 2) {
      moveBackward(60);
      delay(200);
      checkRight(60, 350);
      if (color == 2) {
        return;
      }
      checkRight(60, 350);
      if (color == 2) {
        return;
      }
   } else {
      return;
   }
  
    checkRight(60, 350);
    if (color != 2) {
      moveBackward(60);
      delay(200);
      checkLeft(60, 350);
      if (color == 2) {
        return;
      }
      checkLeft(60, 350);
    }  
  
}

/*
// Function to move forward and stop when blue tape is detected
void stopAtBlue() {
  int color = determineColor();
  while (color != 2) {
    moveForward();
    color = determineColor();
  }
  completeStop();
  while(1);
}
*/
// Function to move bot along 90 degree blue arc
// Assumes path arcs to the left
void blueArc90() {
  int color = determineColor();
  // While on blue path, move forward
  while (color == 2) {
    moveForward(60);
    color = determineColor();
  }
  // When path is no longer blue, turn left to find path
  while (color != 2) {
    turnLeft(60);
    color = determineColor();
  }
  // Need to run this in the loop function or put a continuous loop in!
}
/*
// Function to turn right on red and left on blue
void rightRedLeftBlue() {
  int color = determineColor();
  while (color != 2 && color != 3) {
    moveForward();
    color = determineColor();
  }
  // If bot reaches blue path, turn left
  if (color == 2) {
    turnLeft90();
  }
  // If bot reaches red path, turn right
  if (color == 3) {
    turnRight90();
  }
}

// Function to move along blue line, turn right on red line, stop at yellow path
void demo() {
  int color = determineColor();
  // While on blue path, move forward
  int blue = true;
  while (blue) {
    while (color == 2) {
      moveForward();
      color = determineColor();
    }
    // When off blue path, check if reached red or just drifted
    if (color == 3) {
      // If reached red line, turn right and stop searching for blue path
      turnRight90();
      exit;
    }
    else {
      // If drifted but did not reach red line, correct back to blue
      // Check left for path
      int turns = 0;
      while (color != 2 && turns < 4) {
        turnLeft();
        delay(210);
        color = determineColor();
        turns++;
      }
      // If bot turns 90 degrees and has not found path, go back to center and check right
      if (color != 2) {
        turnRight90();
        while (color !=2 && turns < 4) {
          turnRight();
          delay(220);
          color = determineColor();
          turns++;
        }
      }
    }
  }
  // Now bot has turned right on red line
  // Move forward until find yellow line
  while (color != 1) {
    moveForward();
    color = determineColor();
  }
  // Found yellow path, so stop
  completeStop();
}
*/


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

void moveForward(int speed) {
    motorSpeed1 = speed;
    motorSpeed2 = speed - 7;
    turnMotorClock1();
    turnMotorCounter2();
}

void moveBackward(int speed) {
    motorSpeed1 = speed;
    motorSpeed2 = speed - 7;
    turnMotorClock2();
    turnMotorCounter1();
}

void turnLeft(int speed) {
    motorSpeed2 = speed;
    motorSpeed1 = 0;
    turnMotorCounter2();
    turnMotorCounter1();    
}

void turnRight(int speed) {
    motorSpeed1 = speed;
    motorSpeed2 = speed;
    stopMotor2();
    turnMotorClock1();
    turnMotorClock2();    
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

