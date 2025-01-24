//Lab 1, Ex6

#define LED_RED 4    // Pin for red LED
#define LED_GREEN 5  // Pin for green LED
#define BUTTON 2     // Pin for button

bool buttonPressed = false; // Tracks button state
unsigned long lastDebounceTime = 0; // For debounce logic
unsigned long debounceDelay = 500; // Debounce delay in milliseconds

void setup() {
  Serial.begin(9600);

  // Initialize I/Os
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Button with pull-up resistor
  
  // Ensure LEDs are off initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {
  static bool sequenceRunning = false; // Tracks the state of the LED sequence
  static int currentStep = 0;          // Tracks the current step in the LED sequence
  static unsigned long lastStepTime = 0; // Tracks time for each step

  // Read button state with debounce logic
  int buttonState = digitalRead(BUTTON);
  if (buttonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    buttonPressed = !buttonPressed; // Toggle the buttonPressed state
    sequenceRunning = buttonPressed; // Start/stop sequence based on button state
  }

  // If the sequence is running, execute LED sequence
  if (sequenceRunning) {
    unsigned long currentTime = millis();
    if (currentTime - lastStepTime >= 500) { // Change step every 500ms
      lastStepTime = currentTime;
      executeSequenceStep(currentStep); // Execute the current step
      currentStep = (currentStep + 1) % 6; // Loop through 6 steps
    }
  } else {
    // Ensure all LEDs are turned off when sequence is stopped
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
  }
}

void executeSequenceStep(int step) {
  // Turn off all LEDs initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  // Turn on LEDs based on the current step
  switch (step) {
    case 0:
      digitalWrite(LED_RED, HIGH); // R
      Serial.println("Red");
      break;
    case 1:
      digitalWrite(LED_RED, HIGH); // RG
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("Red and Green");
      break;
    case 2:
      digitalWrite(LED_RED, HIGH); // RGB
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("Red, Green, and Blue");
      break;
    case 3:
      digitalWrite(LED_GREEN, HIGH); // GB
      Serial.println("Green and Blue");
      break;
    case 4:
      Serial.println("Blue"); // Print Blue
      break;
    case 5:
      digitalWrite(LED_RED, HIGH); // RB
      Serial.println("Red and Blue");
      break;
  }
}

