const int buttonPin = 8;
const int ledPin = 13;
const int motorPin = 9;
const int vrxPin = A0;

bool motorState = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(motorPin, LOW); // Ensure motor is off initially
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  int vrxValue = analogRead(vrxPin);
  Serial.print("X-Achse: ");
  Serial.println(analogRead(vrxPin));

  if (buttonState == LOW) {
    motorState = !motorState;
    digitalWrite(ledPin, motorState ? HIGH : LOW);
    digitalWrite(motorPin, motorState ? HIGH : LOW);
    delay(500); // Debounce delay
  }

  if (!motorState) {
    int motorSpeed = map(vrxValue, 0, 1023, 0, 255);
    analogWrite(motorPin, motorSpeed);
  }

  delay(50); // Small delay to stabilize readings
}
