//// Program to flash red and blue LEDs and find path using photodiode

// Constants for photo sensors
int bluePin = 6;
int redPin = 7;
int photoPin = A1;
int path = 0;
  // 1 = yellow
  // 2 = blue
  // 3 = red
  // 4 = black
int voltage = 0;
int threshold = 90;
int flashTime = 125;
bool onBlue = false;
int color = 0;
bool lastCheck= 1; // 0 = left, 1 = right

// Constants for hall sensor
int hallPin = 8;
int hallLED = 9;

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
  // For motors
  Serial.begin(9600);
  pinMode(motorPos1, OUTPUT);
  pinMode(motorNeg1, OUTPUT);
  pinMode(motorPos2, OUTPUT);
  pinMode(motorNeg2, OUTPUT);
  
  // For photosensor
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(photoPin, INPUT);
  completeStop();

  // For hall effect sensor
  pinMode(hallPin, INPUT);
  pinMode(hallLED, OUTPUT);
  digitalWrite(hallLED, LOW);
}

void loop() {
  // Determine path color
  //stopAtBlue();
<<<<<<< HEAD
  color = determineColor(); 
  demo();
=======
  color = determineColor();
  motorSpeed1 = 60;
  //turnMotorCounter1();
  moveForward(60);
  //demo();
>>>>>>> c74da2d4e874f8c703361757601c983e2fddd401
  //rightRedLeftBlue();
  //blueArc90();
  //followBlue();
  //while (color == 3) {
   // completeStop();
  //}

  // test hall effect sensor
<<<<<<< HEAD
   pedestrian();
=======
  //pedestrian();
>>>>>>> c74da2d4e874f8c703361757601c983e2fddd401
}


/*****************
 PHOTO SENSOR FUNCTIONS
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
    digitalWrite(redPin, LOW); 
    return path; 
}



void checkLeft(int speed, int time) {
  turnLeft(speed);
  delay(time);
  color = determineColor();  
}

void checkRight(int speed, int time) {
  turnRight(speed);
  delay(time);
  color = determineColor();
}


// Function to move along blue path in straight line
// In order to work, this function will need to be in the main loop by itself.
// Otherwise it will go forward until it drifts off the path once, correct itself,
// and then stop.
void followBlue() {
  color = determineColor();
  while (color == 2) {
    moveForward(45);
    color = determineColor();
  }
  if (color == 3) {
    return;
  }
  
  completeStop();
  delay(200);
  turnLeft(60);
  delay(500);
  completeStop();
  delay(200);
  moveForward(150);
  delay(150);
  completeStop();
  color = determineColor();
  if (color == 3) {
    return;
  }
  if (color == 2) {
    moveForward(70);
    delay(300);
    completeStop();
    delay(10);
    turnRight(60);
    delay(150);
    completeStop();
    delay(200);
  }

  if (color != 2) {
    delay(500);
    moveBackward(150);
    delay(180);
    completeStop();
    delay(200);
    turnRight(60);
    delay(650);
    completeStop();
    delay(200);
    moveForward(70);
    delay(100);
    completeStop();
    color = determineColor();    
  }
  
} 

void followRed() {
  color = determineColor();
  while (color == 3) {
    moveForward(55);
    color = determineColor();
  }
 
  if (color == 1) {
    return;
  }
  
  completeStop();
  delay(200);
  turnLeft(60);
  delay(500);
  completeStop();
  delay(200);
  moveForward(150);
  delay(150);
  completeStop();
  color = determineColor();
 
  if (color == 1) {
    return;
  }
  
  if(color == 3) {
    moveForward(70);
    delay(300);
    completeStop();
    delay(10);
    turnRight(60);
    delay(150);
    completeStop();
    delay(200);
  }

  if (color != 3) {
    delay(500);
    moveBackward(150);
    delay(180);
    completeStop();
    delay(200);
    turnRight(60);
    delay(1000);
    completeStop();
    delay(200);
    color = determineColor();    
  }
  
} 

  
  /*int turns = 0;
  while (color == 2) {
    moveForward(55);
    color = determineColor();
  }

  completeStop();
  moveBackward(60);
  delay(300);
  completeStop();
  delay(10);
  
  while (color != 2 && turns <= 2) {
    checkLeft(60, 50);
    turns++;
  }

  if (color == 2) {
    //turnLeft(60);
    //jdelay(100);
    moveForward(50);
    delay(100);
  } else {
    moveBackward(80);
    delay(300);
    while (color != 2) {
      checkRight(60, 50);
    }
    turnLeft(70);
    delay(900);
    moveForward(50);
    delay(100);
  } */

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
   color = determineColor();
  while (color == 2) {
    moveForward(50);
    color = determineColor();
  }
  if (color == 3) {
    return;
  }
  
  completeStop();
  delay(200);
  turnLeft(60);
  delay(1500);
  completeStop();
  delay(200);
  moveForward(150);
  delay(150);
  completeStop();
  color = determineColor();
  if(color == 2) {
    moveForward(70);
    delay(300);
    completeStop();
    delay(10);
    turnRight(60);
    delay(80);
    completeStop();
    delay(200);
  }
  if (color == 3) {
    return;
  }
  if (color != 2) {
    delay(500);
    moveBackward(150);
    delay(180);
    completeStop();
    delay(200);
    turnRight(60);
    delay(2000);
    completeStop();
    delay(200);
    color = determineColor();    
}
}

// Function to turn right on red and left on blue
void rightRedLeftBlue() {
  int color = determineColor();
  while (color != 2 && color != 3) {
    moveForward(55);
    color = determineColor();
  }
  // If bot reaches blue path, turn left
  if (color == 2) {
    turnLeft(80);
    delay(800);
    while(1) {
      completeStop();
    }
  }
  // If bot reaches red path, turn right
  if (color == 3) {
    turnRight(80);
    delay(800);
    while(1) {
      completeStop();
    }
  }
}

// Function to move along blue line, turn right on red line, stop at yellow path
void demo() {
  while(color != 3) {
    followBlue();
  }
  if (color == 3) {
    turnRight(80);
    delay(600);
    while (color != 1) {
      followRed();
    }
    if (color == 1) {
      completeStop();
      while(1);
    }  
  }
}




/*****************
 HALL EFFECT SENSOR FUNCTIONS
 *****************/

void pedestrian() {
  // When Hall sensor detects pedestrian, (south pole, high voltage), light up LED
  while (digitalRead(hallPin) == HIGH) {
    digitalWrite(hallLED, HIGH);
  }
  // When hall sensor no longer detects pedestrian, turn LED off 
  digitalWrite(hallLED, LOW);
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
    motorSpeed1 = speed;
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

