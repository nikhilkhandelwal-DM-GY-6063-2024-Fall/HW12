// Pin Definitions
const int potPin = A0;         // Potentiometer pin
const int button1Pin = 2;      // Push button 1 pin
const int button2Pin = 3;      // Push button 2 pin
const int greenLEDPin = 9;     // Green LED pin for success
const int redLEDPin = 10;      // Red LED pin for failure

// Variables
int currentStep = 0;           // Tracks the user's progress in the password sequence

void setup() {
  // Pin Modes
  pinMode(potPin, INPUT);
  pinMode(button1Pin, INPUT_PULLUP);  // Pull-up resistor for Button 1
  pinMode(button2Pin, INPUT_PULLUP);  // Pull-up resistor for Button 2
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Initialize Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Read Inputs
  int potValue = analogRead(potPin);           // Potentiometer value (0-1023)
  int button1State = digitalRead(button1Pin);  // Button 1 state
  int button2State = digitalRead(button2Pin);  // Button 2 state


  // Password Sequence Logic
  switch (currentStep) {
    case 0: // Step 1: Potentiometer in the middle position
      if (potValue > 500 && potValue < 550) {
        Serial.println("Step 1 Passed: Potentiometer in middle position.");
        currentStep++;
        delay(200); // Debounce
      } else if (button1State == LOW || button2State == LOW) {
        signalFailure();
      }
      break;

    case 1: // Step 2: Button 1 Pressed
      if (button1State == LOW) {
        Serial.println("Step 2 Passed: Button 1 pressed.");
        currentStep++;
        delay(200); // Debounce
      } else if (button2State == LOW || potValue < 500 || potValue > 550) {
        signalFailure();
      }
      break;

    case 2: // Step 3: Button 2 Pressed
      if (button2State == LOW) {
        Serial.println("Step 3 Passed: Button 2 pressed.");
        currentStep++;
        delay(200);
      } else if (button1State == LOW || potValue < 500 || potValue > 550) {
        signalFailure();
      }
      break;

    case 3: // Step 4: Potentiometer at maximum position
      if (potValue > 950) {
        Serial.println("Step 4 Passed: Potentiometer at maximum.");
        currentStep++;
        delay(200);
      } else if (button1State == LOW || button2State == LOW) {
        signalFailure();
      }
      break;

    case 4: // Step 5: Button 1 Pressed again
      if (button1State == LOW) {
        Serial.println("Step 5 Passed: Button 1 pressed again.");
        signalSuccess();
        resetSequence();
      } else if (button2State == LOW || potValue < 950) {
        signalFailure();
      }
      break;

    default: // If anything goes wrong, reset
      signalFailure();
      break;
  }
}

void signalSuccess() {
  Serial.println("Password Correct! Success.");
  digitalWrite(greenLEDPin, HIGH);  // Turn on green LED
  delay(1000);
  digitalWrite(greenLEDPin, LOW);   // Turn off green LED
}

void signalFailure() {
  Serial.println("Password Incorrect! Failure.");
  for (int i = 0; i < 3; i++) {     // Blink red LED 3 times
    digitalWrite(redLEDPin, HIGH);
    delay(300);
    digitalWrite(redLEDPin, LOW);
    delay(300);
  }
  resetSequence();
}

void resetSequence() {
  Serial.println("Resetting Sequence...");
  currentStep = 0;  // Reset password progress
  delay(500);
}
