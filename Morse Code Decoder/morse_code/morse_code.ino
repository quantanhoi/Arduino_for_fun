const int buttonPin = 8;
const int ledPin = 13;

String morseCode = "";
unsigned long buttonPressTime = 0;
bool isButtonPressed = false;
unsigned long lastPressTime = 0;
const unsigned long letterSpaceDuration = 1000; // Time to determine end of a letter
const unsigned long wordSpaceDuration = 5000;  // Time to determine end of a word

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Morse Code Decoder Ready");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !isButtonPressed) {
    buttonPressTime = millis();
    isButtonPressed = true;
  }

  if (buttonState == HIGH && isButtonPressed) {
    unsigned long pressDuration = millis() - buttonPressTime;
    if (pressDuration < 200) {
      morseCode += ".";
      blinkLED(0);
    } else {
      morseCode += "-";
      blinkLED(1);
    }
    isButtonPressed = false;
    lastPressTime = millis();
  }

  if (millis() - lastPressTime > letterSpaceDuration && morseCode.length() > 0) {
    char decodedChar = decodeMorse(morseCode);
    Serial.print(decodedChar);
    morseCode = "";
  }

  if (millis() - lastPressTime > wordSpaceDuration) {
    Serial.print(" ");
    lastPressTime = millis();  // Reset lastPressTime to avoid multiple spaces
  }
}

void blinkLED(bool length) {
  if(length) {
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}

char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  return '?'; // Unknown character
}
