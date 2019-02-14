// Program to flash red and blue LEDs and find path using photodiode

int bluePin = 6;
int redPin = 7;
int photoPin = A1;
int path = 0;
  // 1 = yellow
  // 2 = red
  // 3 = blue
  // 4 = black
int voltage = 0;
int threshold = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  digitalWrite(bluePin,HIGH);
  delay(1000);
  voltage = analogRead(photoPin);
  Serial.println(voltage);
  digitalWrite(bluePin,LOW);
  digitalWrite(redPin,HIGH);
  delay(1000);
  voltage = analogRead(photoPin);
  Serial.println(voltage);
  digitalWrite(redPin,LOW);
  


}

void findColor() {
  digitalWrite(bluePin, HIGH);
  delay(1000);
  voltage = analogRead(photoPin);
  if (voltage > threshold) {
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
      delay(1000);
      analogRead(photoPin);
      if (voltage > threshold) {
        path = 1; // yellow
      }
      else {
        path = 2; // red
      }
    }
    else {
      digitalWrite(bluePin, LOW);
      digitalWrite(redPin, HIGH);
      delay(1000);
      voltage = analogRead(photoPin);
      if (voltage > threshold) {
        path = 3; // blue
      }
      else {
        path = 4; // black
      }
    }  
}

