// Logic to control a state machine with 5 states. 
int blueLED = 4;
int redLED = 5;
int greenLED = 6;
int yellowLED = 7;
int yellowLED2 = 8;

int sleepButton = 2;
int diagButton = 3;
int runButton = 18;
int powerButton = 19;

int switch1 = 21;
int switch2 = 20;
int potent1 = A0;
int potent2 = A1;

unsigned long greenFadeMilli = 0;
unsigned long greenBlinkMilli = 0;
unsigned long blueBlinkMilli = 0;
unsigned long yellowBlinkMilli = 0;
int blueFreq;
volatile int currState = 0;   // 0 = off, 1 = on, 2 = run, 3 = sleep, 4 = diagnostic


void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(yellowLED2, OUTPUT);

  pinMode(potent1, INPUT);
  pinMode(potent2, INPUT);
  
  pinMode(powerButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(powerButton), power, CHANGE); 
  
  pinMode(sleepButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sleepButton), sleep, CHANGE); 

  pinMode(diagButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(diagButton), diag, CHANGE); 

  pinMode(runButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(runButton), runing, CHANGE); 

  pinMode(switch1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switch1), switching1on, FALLING);
  
  pinMode(switch2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switch2), switching2on, RISING);
}

// Switches to 'on' if 'off' and vice versa
void power() {
  if (currState == 0) {
    currState = 1;
  } else {
    currState = 0;
  }
}

// Switches to 'run' state
void runing() {
  if (currState != 0) {
    currState = 2; 
    blueFreq = 500;
  }
}

// Switches to 'sleep' state
void sleep() {
  if (currState != 0) {
    currState = 3;
  }
}

// Switches to 'diagnostic' state
void diag() {
  if (currState != 0) {
    currState = 4;
  }  
}



void sleepState() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(yellowLED2, LOW);
  
  int fadeValue = 255;

  // Blinks blue LED 3 times
  for (int i = 0; i < 3; i++) {
    if (currState != 3) {
      return;
    }
    digitalWrite(blueLED, HIGH);
    delay(250);
    digitalWrite(blueLED, LOW);
    delay(250);
  }

  // Fades blue LED 
  while (fadeValue >= 0) {
    if (currState != 3) {
      return;
    }
    analogWrite(blueLED, fadeValue);
    delay(4);
    fadeValue--;
  }

  while(currState == 3);  // Stays asleep
}


void diagState(int probs) {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW); 
  digitalWrite(yellowLED, LOW);
  digitalWrite(yellowLED2, LOW);
  delay(300);

  // Blinks red LED number of times equal to problems
  for (int i = 0; i < probs; i++) {
    digitalWrite(redLED, HIGH);
    delay(400);
    digitalWrite(redLED, LOW);
    delay(400);
  }

  delay(1000);
  currState = 1;
}


void offState() {
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(yellowLED2, LOW);
}

void onState() {
  // Everything off except blinking red LED
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(yellowLED2, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, HIGH);
  delay(50);
  digitalWrite(redLED, LOW);
  delay(50);
}

void switching1on() {
  if (currState == 2 && digitalRead(switch1) == LOW) {
    blueFreq = 50;
  }
}

void switching2on() {
  if (currState == 2 && blueFreq == 50 && digitalRead(switch2) == HIGH) {
    digitalWrite(redLED, HIGH);
  }
}

void runState() {
    int fadeValue = 255;
    int numBlinks = 0;
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
  
    while (currState == 2) {
       int brightness = analogRead(potent1) / 4;
       int yellowPeriod = analogRead(potent2) / 4;  
       
       if (numBlinks > 3 || fadeValue > 0) {
        analogWrite(greenLED, fadeValue);
       }
       unsigned long currentMilli = millis();

       // Fades green LED
       if (currentMilli - greenFadeMilli >= 23 && fadeValue > 0) {
            greenFadeMilli = currentMilli;
            fadeValue--;
       }

       // Blinks green LED after fade
       if (fadeValue <= 0) {
         currentMilli = millis();
         if (currentMilli - greenBlinkMilli >= 500) {
            greenBlinkMilli = currentMilli;
            if (digitalRead(greenLED) == LOW) {
              digitalWrite(greenLED, HIGH);
            } else {
              digitalWrite(greenLED, LOW);
              numBlinks++;
              if (numBlinks > 3) {
                fadeValue = 255;
                numBlinks = 0;
              }
            }     
         }
       }

       // Run state blue LED blinking
       currentMilli = millis();
       if (currentMilli - blueBlinkMilli >= blueFreq) {
          blueBlinkMilli = currentMilli;
          if (digitalRead(blueLED) == LOW) {
            digitalWrite(blueLED, HIGH);
          } else {
            digitalWrite(blueLED, LOW);
          }
       } 
       
       if (blueFreq == 500) {
         digitalWrite(redLED, LOW); 
       }

     analogWrite(yellowLED, brightness);

     // Blinks yellow LED number two
     currentMilli = millis();
     if (currentMilli - yellowBlinkMilli >= yellowPeriod) {
        yellowBlinkMilli = currentMilli;
        if (digitalRead(yellowLED2) == HIGH) {
          digitalWrite(yellowLED2, LOW);
        } else {
          digitalWrite(yellowLED2, HIGH);
        }
     } 
    }
}

void loop() {
   if (currState == 0) {
      offState();
   } else if (currState == 1) {
      onState();
   }  else if (currState == 2) {
      runState();
   } else if (currState == 3) {
      sleepState();
   } else if (currState = 4) {
      diagState(5);
   }
}
