int fastPWM = 5;
int signalPin = 12;

void setup()
{
  pinMode(fastPWM, OUTPUT);
  pinMode(signalPin, OUTPUT);
  
  Serial.begin(9600);

  //Serial1.begin(1200);

  TCCR3A = _BV(COM3A0) | _BV(COM3B0) | _BV(WGM30) | _BV(WGM31);
 
  // sets COM Output Mode to FastPWM with toggle of OC3A on compare match with OCR3A

  // also sets WGM to mode 15: FastPWM with top set by OCR3A

  TCCR3B = _BV(WGM32) | _BV(WGM33) |  _BV(CS31);

  // sets WGM as stated above; sets clock scaling to "divide by 8"

  OCR3A = 53;

  // above sets the counter value at which register resets to 0x0000;

  // generate 18.523 kHz when OCR3A=53 on Mega pin 5

  // Serial.println(TCCR3A, BIN);Serial.println(TCCR3B, BIN);

}

void loop()
{
      digitalWrite(signalPin, HIGH);
      delay(400);
      digitalWrite(signalPin, LOW);
      delay(400);
      delay(1000);
}
