// Program to flash red and blue LEDs and find path using photodiode

//#include <Motion_Equations.ino>

int bluePin = 6;
int redPin = 7;
int photoPin = A1;
int path = 0;
  // 1 = yellow
  // 2 = red
  // 3 = blue
  // 4 = black
int voltage = 0;
int threshold = 80;


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

/*void followBlue() {
  int color = determineColor();
  while (color != 2) {
    // turn some number of degrees
    // determine color again
  }
  // move forward 
}*/

