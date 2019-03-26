int TCC = A15; // will need to change this to whatever pin the microphone output is


void setup() {
  // put your setup code here, to run once:
  pinMode(TCC, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int v = digitalRead(TCC);
  //Serial.println(v);
  //delay(10);
  
  int TCCLength = findLength();
  Serial.println(TCCLength);
  delay(100);
  
}

int findLength() {
    // Wait until there's a signal from TCC
    while(digitalRead(TCC) == HIGH) {
    }
    // Get time
    unsigned long startMillis = millis();
    // Wait until signal from TCC ends
    while (digitalRead(TCC) == HIGH) {
    }
    // Get current time
    unsigned long currentMillis = millis();
    // Find time passed since start of signal
    int duration = currentMillis - startMillis;
    
    // this was being used for testing with the function generator
    /*if (duration < (10 - tolerance)) {
      return 0;
    }
    else {
      return 10;
    }
    */

    int tolerance = 10;
    
    // See if the signal is less than 200 ms long
    if (duration < (200 - tolerance)) {
      return 0;
    }
    // See if the signal is 200 ms
    if (duration >= (200 - tolerance) && duration < (200 + tolerance)) {
      return 200;
    }
    // See if the signal is 300 ms
    if (duration >= (300 - tolerance) && duration < (300 + tolerance)) {
      return 300;
    }
    // See if the signal is 400 ms
    if (duration >= (400 - tolerance) && duration < (400 + tolerance)) {
      return 400;
    }
    // Or is it something longer
    else {
      return 1000;
    }
}


