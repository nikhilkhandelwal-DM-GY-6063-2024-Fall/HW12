// Pin Definitions
const int potPin = A0; 
const int button1Pin = 2;
const int button2Pin = 3;
const int greenLEDPin = 9; 
const int redLEDPin = 10; 
const int blueLEDPin = 8; 

int currentStep = 0;           // Tracks password progress

void setup() {
  pinMode(potPin, INPUT);
  pinMode(button1Pin, INPUT_PULLUP);  // Pull-up resistor for Button 1
  pinMode(button2Pin, INPUT_PULLUP);  // Pull-up resistor for Button 2
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Read inputs
  int potValue = analogRead(potPin);
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);

  // Blue LED Notification
  if (potValue > 400 && potValue < 500) {  // Middle position
    blinkBlueOnce();
  } else if (potValue > 850) {  // Right-most position
    blinkBlueOnce();
  }

  // Password Sequence Logic
  switch (currentStep) {
    case 0: // Step 1: Potentiometer in middle (400-500)
      if (potValue > 400 && potValue < 500) {
        Serial.println("Step 1 Passed");
        currentStep++;
        delay(200);
      }
      break;

    case 1: // Step 2: Button 1 pressed
      if (button1State == LOW) {
        Serial.println("Step 2 Passed");
        currentStep++;
        delay(200);
      } else if (button2State == LOW) {
        signalFailure();
      }
      break;

    case 2: // Step 3: Button 2 pressed
      if (button2State == LOW) {
        Serial.println("Step 3 Passed");
        currentStep++;
        delay(200);
      } else if (button1State == LOW) {
        signalFailure();
      }
      break;

    case 3: // Step 4: Potentiometer at max position (>850)
      if (potValue > 850) {
        Serial.println("Step 4 Passed");
        currentStep++;
        delay(200);
      } else if (button1State == LOW || button2State == LOW) {
        signalFailure();
      }
      break;

    case 4: // Step 5: Button 1 pressed again
      if (button1State == LOW) {
        Serial.println("Step 5 Passed: Password Correct!");
        signalSuccess();
        resetSequence();
      } else if (button2State == LOW) {
        signalFailure();
      }
      break;

    default: // Failure condition
      signalFailure();
      break;
  }
}

void signalSuccess() {
  Serial.println("Success!");
  for (int i = 0; i < 3; i++) { // Blink green LED 3 times
    digitalWrite(greenLEDPin, HIGH);
    delay(300);
    digitalWrite(greenLEDPin, LOW);
    delay(300);
  }
}

void signalFailure() {
  Serial.println("Failure!");
  for (int i = 0; i < 3; i++) { // Blink red LED 3 times
    digitalWrite(redLEDPin, HIGH);
    delay(300);
    digitalWrite(redLEDPin, LOW);
    delay(300);
  }
  resetSequence();
}

void resetSequence() {
  Serial.println("Resetting...");
  currentStep = 0;
  delay(500);
}

void blinkBlueOnce() {
  digitalWrite(blueLEDPin, HIGH);
  delay(300);
  digitalWrite(blueLEDPin, LOW);
  delay(300);
}
