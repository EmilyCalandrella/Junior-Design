int microphone = A15; // will need to change this to whatever pin the microphone output is


void setup() {
  // put your setup code here, to run once:
  pinMode(microphone, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //int v = digitalRead(microphone);
  //Serial.println(v);
  //delay(10);
  
  int TCCLength = findLength();
  Serial.println(TCCLength);
  delay(100);
  
}

int findLength() {
    // Wait until there's a signal from TCC
    while(analogRead(microphone) < 5) {
      //Serial.println(analogRead(microphone));
    }
    // Get time
    unsigned long startMillis = millis();
    // Wait until signal from TCC ends
    while (analogRead(microphone) > 30) {
      //Serial.println(analogRead(microphone));
    }
    // Get current time
    unsigned long currentMillis = millis();
    // Find time passed since start of signal
    int duration = currentMillis - startMillis;
    Serial.println(duration);
    
    // this was being used for testing with the function generator
    /*if (duration < (10 - tolerance)) {
      return 0;
    }
    else {
      return 10;
    }
    */

    int lowTolerance = 50;
    int highTolerance = 30;
    
    // See if the signal is less than 200 ms long
    if (duration < (200 - lowTolerance)) {
      return 0;
    }
    // See if the signal is 200 ms
    // message_1
    if (duration >= (200 - lowTolerance) && duration < (200 + highTolerance)) {
      return 200;
    }
    // See if the signal is 300 ms
    // message_2
    if (duration >= (300 - lowTolerance) && duration < (300 + highTolerance)) {
      return 300;
    }
    // See if the signal is 400 ms
    // message_3
    if (duration >= (400 - lowTolerance) && duration < (400 + highTolerance)) {
      return 400;
    }
    // See if the signal is 500 ms
    // message_4
    if (duration >= (500 - lowTolerance) && duration < (500 + highTolerance)) {
      return 500;
    }
    // Or is it something longer
    else {
      return 1000;
    }
}


