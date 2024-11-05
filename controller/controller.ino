int analogPin = A0;   
int pwmPin3 = 3; // OC2B - Pin 3

void setup() {
  // Initialize Serial
  Serial.begin(9600);

  // Set pin 3 for PWM
  pinMode(pwmPin3, OUTPUT);

  // Configure Timer 2 for Fast PWM mode
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS00);
}

int darkCounter = 0, lightCounter = 0;

void loop() {
  int val = analogRead(analogPin);
  
  // Testing purposes
  Serial.print("Analog Value: ");
  Serial.println(val);
  Serial.print("Light Counter: ");
  Serial.println(lightCounter);
  Serial.print("Dark Counter: ");
  Serial.println(darkCounter);

  if (val > 300) {
    lightCounter++;
    darkCounter = 0;
  } else {
    darkCounter++;
    lightCounter = 0;
  }
  
  if (val > 300 && lightCounter >= 5) { // light 
    OCR2B = 0;
  } else if (darkCounter >= 5) { // dark
    // OCR2B = 178 is 70% duty cycle
    // OCR2B = 77 is 30% duty cycle
    if (val < 100) {
      OCR2B = 178;
      delay(5000);
    } else if (val < 200) {
      OCR2B = 163;
      delay(5000);
    } else if (val <= 300) {
      OCR2B = 148;
      delay(5000);
    }
    Serial.print("OCR2B: ");
    Serial.println(OCR2B);
  }
  delay(1000);
}