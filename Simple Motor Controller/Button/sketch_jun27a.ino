const int buttonPin = 8;
const int ledPin = 13;
const int motorPin = 9;

bool motorState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(motorPin, LOW);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  static int lastButtonState = HIGH;
  
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW) {
      motorState = !motorState;
      digitalWrite(ledPin, motorState ? HIGH : LOW);
      digitalWrite(motorPin, motorState ? HIGH : LOW);
      Serial.print("Motor State: ");
      Serial.println(motorState ? "ON" : "OFF");
    }
  }
  
  lastButtonState = buttonState;
}
